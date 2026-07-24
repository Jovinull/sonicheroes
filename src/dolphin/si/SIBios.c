#include "dolphin/os.h"

#define SI_MAX_CHAN               4
#define SI_MAX_TYPE               4
#define SI_COMCSR_IDX             13
#define SI_STATUS_IDX             14
#define SI_COMCSR_TCINT_MASK      0x80000000
#define SI_COMCSR_TCINTMSK_MASK   0x40000000
#define SI_COMCSR_COMERR_MASK     0x20000000
#define SI_COMCSR_RDSTINT_MASK    0x10000000
#define SI_COMCSR_RDSTINTMSK_MASK 0x08000000
#define SI_COMCSR_TSTART_MASK     1
#define SI_ERROR_NO_RESPONSE      8
#define SI_ERROR_BUSY             0x80
#define ROUND(n, a)               (((u32)(n) + (a) - 1) & ~((a) - 1))

typedef void (*SICallback)(s32 chan, u32 error, OSContext* context);
typedef void (*SITypeCallback)(s32 chan, u32 type);

typedef struct SIPacket {
	s32 chan;
	void* output;
	u32 outputBytes;
	void* input;
	u32 inputBytes;
	SICallback callback;
	OSTime fire;
} SIPacket;

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

typedef struct OSAlarmLink {
	OSAlarm* prev;
	OSAlarm* next;
} OSAlarmLink;

struct OSAlarm {
	OSAlarmHandler handler;
	u32 tag;
	OSTime fire;
	OSAlarmLink link;
	OSTime period;
	OSTime start;
};

#ifdef __MWERKS__
extern volatile u32 __SIRegs[64] : 0xCC006400;
extern u32 __OSBusClock : 0x800000F8;
#else
extern volatile u32 __SIRegs[64];
extern u32 __OSBusClock;
#endif

#define OS_TIMER_CLOCK              (__OSBusClock / 4)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

extern const char* __SIVersion;
extern OSTime __OSGetSystemTime(void);
extern void OSRegisterVersion(const char* version);
extern void OSCancelAlarm(OSAlarm* alarm);
extern void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler);
extern u32 VIGetCurrentLine(void);
extern void SISetSamplingRate(u32 msec);
extern u16 OSGetWirelessID(s32 chan);
extern void OSSetWirelessID(s32 chan, u16 id);

typedef struct SIControl {
	s32 chan;
	u32 poll;
	u32 inputBytes;
	void* input;
	SICallback callback;
} SIControl;

char lbl_80298B28[] = "<< Dolphin SDK - SI\trelease build: Apr 17 2003 12:33:19 (0x2301) >>";
static SIControl Si = { -1 };
static SIPacket Packet[4];
static OSAlarm Alarm[4];
static u32 Type[4] = { 8, 8, 8, 8 };
struct SITypeStrings {
	char noResponse[12];
	char n64Controller[16];
	char n64Microphone[16];
	char n64Keyboard[16];
	char n64Mouse[12];
	char gameBoyAdvance[16];
	char standardController[20];
	char wirelessReceiver[20];
	char waveBirdController[20];
	char keyboard[12];
	char steering[12];
	u32 terminator;
};
struct SITypeStrings lbl_80298B90 = {
	"No response",
	"N64 controller",
	"N64 microphone",
	"N64 keyboard",
	"N64 mouse",
	"GameBoy Advance",
	"Standard controller",
	"Wireless receiver",
	"WaveBird controller",
	"Keyboard",
	"Steering",
	0,
};
static OSTime TypeTime[4];
static OSTime XferTime[4];
static SITypeCallback TypeCallback[4][4];
static __OSInterruptHandler RDSTHandler[4];
static BOOL InputBufferValid[4];
static u32 InputBuffer[4][2];
static volatile u32 InputBufferVcount[4];

u32 __PADFixBits;
u32 gap_10_8042CF24_sbss;

static u32 CompleteTransfer(void);
static inline void SITransferNext(s32 chan);
static void SIInterruptHandler(s16 interrupt, OSContext* context);
static int __SITransfer(
    s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes, SICallback callback);
static void AlarmHandler(OSAlarm* alarm, OSContext* context);
static void GetTypeCallback(s32 chan, u32 error, OSContext* context);
static BOOL SIGetResponseRaw(s32 chan);
BOOL SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes,
    SICallback callback, OSTime delay);
u32 SIGetType(s32 chan);

BOOL SIBusy(void)
{
	return Si.chan != -1 ? TRUE : FALSE;
}

BOOL SIIsChanBusy(s32 chan)
{
	return Packet[chan].chan != -1 || Si.chan == chan;
}

static inline void SIClearTCInterrupt(void)
{
	u32 reg;

	reg = __SIRegs[SI_COMCSR_IDX];
	reg |= SI_COMCSR_TCINT_MASK;
	reg &= ~SI_COMCSR_TSTART_MASK;
	__SIRegs[SI_COMCSR_IDX] = reg;
}

static u32 CompleteTransfer(void)
{
	u32 sr;
	u32 i;
	u32 rLen;
	u8* input;
	u32 temp;

	sr = __SIRegs[SI_STATUS_IDX];
	SIClearTCInterrupt();

	if (Si.chan != -1) {
		XferTime[Si.chan] = __OSGetSystemTime();
		input             = Si.input;
		rLen              = Si.inputBytes / sizeof(u32);
		for (i = 0; i < rLen; i++) {
			*((u32*)input)++ = __SIRegs[i + 0x20];
		}

		rLen = Si.inputBytes & 3;
		if (rLen != 0) {
			temp = __SIRegs[i + 32];
			for (i = 0; i < rLen; i++) {
				*input++ = temp >> ((3 - i) * 8);
			}
		}

		if (__SIRegs[SI_COMCSR_IDX] & SI_COMCSR_COMERR_MASK) {
			sr >>= (3 - Si.chan) * 8;
			sr &= 0xF;
			if ((sr & 8) != 0 && (Type[Si.chan] & 0x80) == 0) {
				Type[Si.chan] = 8;
			}
			if (sr == 0) {
				sr = 4;
			}
		} else {
			TypeTime[Si.chan] = __OSGetSystemTime();
			sr                = 0;
		}
		Si.chan = -1;
	}
	return sr;
}

static inline void SITransferNext(s32 chan)
{
	int i;
	SIPacket* packet;

	for (i = 0; i < 4; i++) {
		chan++;
		chan %= 4;
		packet = &Packet[chan];
		if (packet->chan != -1 && packet->fire <= __OSGetSystemTime()) {
			if (__SITransfer(packet->chan, packet->output, packet->outputBytes, packet->input,
			        packet->inputBytes, packet->callback)) {
				OSCancelAlarm(&Alarm[chan]);
				packet->chan = -1;
			}
			return;
		}
	}
}

static void SIInterruptHandler(s16 interrupt, OSContext* context)
{
	u32 reg;
	s32 chan;
	u32 sr;
	SICallback callback;
	int i;
	u32 vcount;
	u32 x;

	reg = __SIRegs[SI_COMCSR_IDX];
	if ((reg & (SI_COMCSR_TCINT_MASK | SI_COMCSR_TCINTMSK_MASK))
	    == (SI_COMCSR_TCINT_MASK | SI_COMCSR_TCINTMSK_MASK)) {
		chan        = Si.chan;
		sr          = CompleteTransfer();
		callback    = Si.callback;
		Si.callback = NULL;
		SITransferNext(chan);
		if (callback) {
			callback(chan, sr, context);
		}
		sr = __SIRegs[SI_STATUS_IDX];
		sr &= 0x0F000000 >> (chan << 3);
		__SIRegs[SI_STATUS_IDX] = sr;
		if (Type[chan] == SI_ERROR_BUSY && !SIIsChanBusy(chan)) {
			static u32 cmdTypeAndStatus;
			SITransfer(chan, &cmdTypeAndStatus, 1, &Type[chan], 3, GetTypeCallback,
			    OSMicrosecondsToTicks(65));
		}
	}

	if ((reg & (SI_COMCSR_RDSTINT_MASK | SI_COMCSR_RDSTINTMSK_MASK))
	    == (SI_COMCSR_RDSTINT_MASK | SI_COMCSR_RDSTINTMSK_MASK)) {
		vcount = 1 + VIGetCurrentLine();
		x      = (Si.poll & (0x3FF << 16)) >> 16;
		for (i = 0; i < 4; i++) {
			if (SIGetResponseRaw(i)) {
				InputBufferVcount[i] = vcount;
			}
		}
		for (i = 0; i < 4; i++) {
			if ((Si.poll & (0x80000000 >> (24 + i))) != 0) {
				if (InputBufferVcount[i] == 0 || ((x >> 1) + InputBufferVcount[i]) < vcount) {
					return;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			InputBufferVcount[i] = 0;
		}
		for (i = 0; i < 4; i++) {
			if (RDSTHandler[i] != NULL) {
				RDSTHandler[i](interrupt, context);
			}
		}
	}
}

static BOOL SIEnablePollingInterrupt(BOOL enable)
{
	BOOL enabled;
	BOOL rc;
	u32 reg;
	int i;

	enabled = OSDisableInterrupts();
	reg     = __SIRegs[SI_COMCSR_IDX];
	rc      = (reg & SI_COMCSR_RDSTINTMSK_MASK) != 0 ? TRUE : FALSE;
	if (enable) {
		reg |= SI_COMCSR_RDSTINTMSK_MASK;
		for (i = 0; i < 4; i++) {
			InputBufferVcount[i] = 0;
		}
	} else {
		reg &= ~SI_COMCSR_RDSTINTMSK_MASK;
	}
	reg &= ~(SI_COMCSR_TCINT_MASK | SI_COMCSR_TSTART_MASK);
	__SIRegs[SI_COMCSR_IDX] = reg;
	OSRestoreInterrupts(enabled);
	return rc;
}

BOOL SIRegisterPollingHandler(__OSInterruptHandler handler)
{
	BOOL enabled;
	int i;

	enabled = OSDisableInterrupts();
	for (i = 0; i < 4; i++) {
		if (RDSTHandler[i] == handler) {
			OSRestoreInterrupts(enabled);
			return TRUE;
		}
	}
	for (i = 0; i < 4; i++) {
		if (RDSTHandler[i] == NULL) {
			RDSTHandler[i] = handler;
			SIEnablePollingInterrupt(TRUE);
			OSRestoreInterrupts(enabled);
			return TRUE;
		}
	}
	OSRestoreInterrupts(enabled);
	return FALSE;
}

BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler)
{
	BOOL enabled;
	int i;

	enabled = OSDisableInterrupts();
	for (i = 0; i < 4; i++) {
		if (RDSTHandler[i] == handler) {
			RDSTHandler[i] = NULL;
			for (i = 0; i < 4; i++) {
				if (RDSTHandler[i] != NULL) {
					break;
				}
			}
			if (i == 4) {
				SIEnablePollingInterrupt(FALSE);
			}
			OSRestoreInterrupts(enabled);
			return TRUE;
		}
	}
	OSRestoreInterrupts(enabled);
	return FALSE;
}

void SIInit(void)
{
	OSRegisterVersion(__SIVersion);
	Packet[0].chan = Packet[1].chan = Packet[2].chan = Packet[3].chan = -1;
	Si.poll                                                           = 0;
	SISetSamplingRate(0);
	while (__SIRegs[SI_COMCSR_IDX] & SI_COMCSR_TSTART_MASK) {
	}
	__SIRegs[SI_COMCSR_IDX] = SI_COMCSR_TCINT_MASK;
	__OSSetInterruptHandler(0x14, (__OSInterruptHandler)SIInterruptHandler);
	__OSUnmaskInterrupts(0x800);
	SIGetType(0);
	SIGetType(1);
	SIGetType(2);
	SIGetType(3);
}

static int __SITransfer(
    s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes, SICallback callback)
{
	BOOL enabled;
	u32 rLen;
	u32 i;
	u32 sr;
	union {
		u32 val;
		struct {
			u32 tcint : 1;
			u32 tcintmsk : 1;
			u32 comerr : 1;
			u32 rdstint : 1;
			u32 rdstintmsk : 1;
			u32 pad2 : 4;
			u32 outlngth : 7;
			u32 pad1 : 1;
			u32 inlngth : 7;
			u32 pad0 : 5;
			u32 channel : 2;
			u32 tstart : 1;
		} f;
	} comcsr;

	enabled = OSDisableInterrupts();
	if (Si.chan != -1) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}
	sr = __SIRegs[SI_STATUS_IDX];
	sr &= 0x0F000000 >> (chan * 8);
	__SIRegs[SI_STATUS_IDX] = sr;
	Si.chan                 = chan;
	Si.callback             = callback;
	Si.inputBytes           = inputBytes;
	Si.input                = input;

	rLen = ROUND(outputBytes, 4) / 4;
	for (i = 0; i < rLen; i++) {
		__SIRegs[i + 0x20] = ((u32*)output)[i];
	}

	comcsr.val              = __SIRegs[SI_COMCSR_IDX];
	comcsr.f.tcint          = 1;
	comcsr.f.tcintmsk       = callback ? 1 : 0;
	comcsr.f.outlngth       = outputBytes == 0x80 ? 0 : outputBytes;
	comcsr.f.inlngth        = inputBytes == 0x80 ? 0 : inputBytes;
	comcsr.f.channel        = chan;
	comcsr.f.tstart         = 1;
	__SIRegs[SI_COMCSR_IDX] = comcsr.val;
	OSRestoreInterrupts(enabled);
	return TRUE;
}

u32 SIGetStatus(s32 chan)
{
	BOOL enabled;
	u32 sr;
	int chanShift;

	enabled   = OSDisableInterrupts();
	sr        = __SIRegs[SI_STATUS_IDX];
	chanShift = (3 - chan) * 8;
	sr >>= chanShift;
	if ((sr & 8) != 0 && (Type[chan] & SI_ERROR_BUSY) == 0) {
		Type[chan] = 8;
	}
	OSRestoreInterrupts(enabled);
	return sr;
}

void SISetCommand(s32 chan, u32 command)
{
	__SIRegs[chan * 3] = command;
}

void SITransferCommands(void)
{
	__SIRegs[SI_STATUS_IDX] = SI_COMCSR_TCINT_MASK;
}

u32 SISetXY(u32 x, u32 y)
{
	u32 poll;
	BOOL enabled;

	poll = x << 16;
	poll |= y << 8;
	enabled = OSDisableInterrupts();
	Si.poll &= 0xFC0000FF;
	Si.poll |= poll;
	poll         = Si.poll;
	__SIRegs[12] = poll;
	OSRestoreInterrupts(enabled);
	return poll;
}

u32 SIEnablePolling(u32 poll)
{
	BOOL enabled;
	u32 en;

	if (poll == 0) {
		return Si.poll;
	}
	enabled = OSDisableInterrupts();
	poll >>= 24;
	en = poll & 0xF0;
	poll &= (en >> 4) | 0x03FFFFF0;
	poll &= 0xFC0000FF;
	Si.poll &= ~(en >> 4);
	Si.poll |= poll;
	poll = Si.poll;
	SITransferCommands();
	__SIRegs[12] = poll;
	OSRestoreInterrupts(enabled);
	return poll;
}

u32 SIDisablePolling(u32 poll)
{
	BOOL enabled;

	if (poll == 0) {
		return Si.poll;
	}
	enabled = OSDisableInterrupts();
	poll >>= 24;
	poll &= 0xF0;
	poll         = Si.poll & ~poll;
	__SIRegs[12] = poll;
	Si.poll      = poll;
	OSRestoreInterrupts(enabled);
	return poll;
}

static BOOL SIGetResponseRaw(s32 chan)
{
	u32 sr;

	sr = SIGetStatus(chan);
	if (sr & 0x20) {
		InputBuffer[chan][0]   = __SIRegs[1 + chan * 3];
		InputBuffer[chan][1]   = __SIRegs[2 + chan * 3];
		InputBufferValid[chan] = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL SIGetResponse(s32 chan, void* data)
{
	BOOL rc;
	BOOL enabled;

	enabled = OSDisableInterrupts();
	SIGetResponseRaw(chan);
	rc                     = InputBufferValid[chan];
	InputBufferValid[chan] = FALSE;
	if (rc) {
		((u32*)data)[0] = InputBuffer[chan][0];
		((u32*)data)[1] = InputBuffer[chan][1];
	}
	OSRestoreInterrupts(enabled);
	return rc;
}

static void AlarmHandler(OSAlarm* alarm, OSContext* context)
{
	s32 chan;
	SIPacket* packet;

	chan   = alarm - Alarm;
	packet = &Packet[chan];
	if (packet->chan != -1) {
		if (__SITransfer(packet->chan, packet->output, packet->outputBytes, packet->input,
		        packet->inputBytes, packet->callback)) {
			packet->chan = -1;
		}
	}
}

BOOL SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes,
    SICallback callback, OSTime delay)
{
	BOOL enabled;
	SIPacket* packet;
	OSTime now;
	OSTime fire;

	packet  = &Packet[chan];
	enabled = OSDisableInterrupts();
	if (packet->chan != -1 || Si.chan == chan) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}
	now = __OSGetSystemTime();
	if (delay == 0) {
		fire = now;
	} else {
		fire = delay + XferTime[chan];
	}
	if (now < fire) {
		delay = fire - now;
		OSSetAlarm(&Alarm[chan], delay, AlarmHandler);
	} else if (__SITransfer(chan, output, outputBytes, input, inputBytes, callback)) {
		OSRestoreInterrupts(enabled);
		return TRUE;
	}
	packet->chan        = chan;
	packet->output      = output;
	packet->outputBytes = outputBytes;
	packet->input       = input;
	packet->inputBytes  = inputBytes;
	packet->callback    = callback;
	packet->fire        = fire;
	OSRestoreInterrupts(enabled);
	return TRUE;
}

static inline void CallTypeAndStatusCallback(s32 chan, u32 type)
{
	SITypeCallback callback;
	int i;

	for (i = 0; i < 4; i++) {
		callback = TypeCallback[chan][i];
		if (callback != NULL) {
			TypeCallback[chan][i] = NULL;
			callback(chan, type);
		}
	}
}

static void GetTypeCallback(s32 chan, u32 error, OSContext* context)
{
	u32 type;
	u32 chanBit;
	int fix;
	u32 id;

	Type[chan] &= ~SI_ERROR_BUSY;
	Type[chan] |= error;
	TypeTime[chan] = __OSGetSystemTime();
	type           = Type[chan];
	chanBit        = 0x80000000 >> chan;
	fix            = __PADFixBits & chanBit;
	__PADFixBits &= ~chanBit;

	if ((error & 0xF) != 0 || (type & 0x18000000) != 0x08000000 || (type & 0x80000000) == 0
	    || (type & 0x04000000) != 0) {
		OSSetWirelessID(chan, 0);
		CallTypeAndStatusCallback(chan, Type[chan]);
	} else {
		static u32 cmdFixDevice[4];
		id = OSGetWirelessID(chan) << 8;
		if (fix != 0 && (id & 0x100000) != 0) {
			cmdFixDevice[chan] = 0x4E000000 | (id & 0xCFFF00) | 0x100000;
			Type[chan]         = SI_ERROR_BUSY;
			SITransfer(chan, &cmdFixDevice[chan], 3, &Type[chan], 3, GetTypeCallback, 0);
			return;
		}
		if ((type & 0x00100000) != 0) {
			if ((id & 0xCFFF00) != (type & 0xCFFF00)) {
				if ((id & 0x100000) == 0) {
					id = type & 0xCFFF00;
					id |= 0x100000;
					OSSetWirelessID(chan, id >> 8);
				}
				cmdFixDevice[chan] = 0x4E000000 | id;
				Type[chan]         = SI_ERROR_BUSY;
				SITransfer(chan, &cmdFixDevice[chan], 3, &Type[chan], 3, GetTypeCallback, 0);
				return;
			}
		} else {
			if ((type & 0x40000000) != 0) {
				id = type & 0xCFFF00;
				id |= 0x100000;
				OSSetWirelessID(chan, id >> 8);
				cmdFixDevice[chan] = 0x4E000000 | id;
				Type[chan]         = SI_ERROR_BUSY;
				SITransfer(chan, &cmdFixDevice[chan], 3, &Type[chan], 3, GetTypeCallback, 0);
				return;
			}
			OSSetWirelessID(chan, 0);
		}
		CallTypeAndStatusCallback(chan, Type[chan]);
	}
}

u32 SIGetType(s32 chan)
{
	static u32 cmdTypeAndStatus;
	BOOL enabled;
	u32 type;
	OSTime diff;

	enabled = OSDisableInterrupts();
	type    = Type[chan];
	diff    = __OSGetSystemTime() - TypeTime[chan];
	if ((Si.poll & (0x80 >> chan)) != 0) {
		if (type != 8) {
			TypeTime[chan] = __OSGetSystemTime();
			OSRestoreInterrupts(enabled);
			return type;
		}
		type = Type[chan] = SI_ERROR_BUSY;
	} else {
		if (diff <= OSMillisecondsToTicks(50) && type != 8) {
			OSRestoreInterrupts(enabled);
			return type;
		}
		if (diff <= OSMillisecondsToTicks(75)) {
			Type[chan] = SI_ERROR_BUSY;
		} else {
			type = Type[chan] = SI_ERROR_BUSY;
		}
	}
	TypeTime[chan] = __OSGetSystemTime();
	SITransfer(
	    chan, &cmdTypeAndStatus, 1, &Type[chan], 3, GetTypeCallback, OSMicrosecondsToTicks(65));
	OSRestoreInterrupts(enabled);
	return type;
}

u32 SIGetTypeAsync(s32 chan, SITypeCallback callback)
{
	BOOL enabled;
	u32 type;
	int i;

	enabled = OSDisableInterrupts();
	type    = SIGetType(chan);
	if ((Type[chan] & SI_ERROR_BUSY) != 0) {
		for (i = 0; i < SI_MAX_TYPE; i++) {
			if (TypeCallback[chan][i] == callback) {
				break;
			}
			if (TypeCallback[chan][i] == NULL) {
				TypeCallback[chan][i] = callback;
				break;
			}
		}
	} else {
		callback(chan, type);
	}
	OSRestoreInterrupts(enabled);
	return type;
}
