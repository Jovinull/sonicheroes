#include "types.h"
// Functions below marked static inline without being helpers: they are real
// SDK API this game never calls, and the original linker stripped them from
// the DOL. The inline marking keeps their bodies out of the object so the
// section sizes match the original exactly; the code stays for SDK fidelity.

#include "dolphin/os.h"

// The GameCube controller driver, the Dolphin SDK's pad library. WORK IN
// PROGRESS.
//
// The translation unit runs from UpdateOrigin at 0x801DDD9C to
// __PADDisableRecalibration's end at 0x801DF6E4. The boundaries are not
// guesses: the two functions before UpdateOrigin are Padclamp.c, the SDK's
// companion file that links just ahead of this one (see the header there),
// and the function at 0x801DF6E4 is the ar library's callback-swap on its own
// .sbss word, followed at 0x801DF728 by stores to the ARAM DMA registers at
// 0xCC005000. Inside the range every function works the SI joy-bus machinery,
// and __PADDisableRecalibration at 0x801DF668 carries its real name in the
// symbol map.
//
// The identity of the library is not a guess either: the version string in
// this unit's .data at 0x80293058 reads
// "<< Dolphin SDK - PAD	release build: Aug  6 2003 04:30:02 (0x2301) >>",
// and PADInit passes its address to OSRegisterVersion.
//
// Sections, read off the disc:
//   .data   0x80293058  the version string, then ResetFunctionInfo
//   .bss    0x803F30F0  Type[4], Origin[4], cmdFixDevice[4]
//   .sdata  0x8042BFA0  __PADVersion, ResettingChan, XPatchBits, AnalogMode,
//                       Spec, MakeStatus, cmdReadOrigin, cmdCalibrate
//   .sbss   0x8042CCD8  Initialized, EnabledBits, ResettingBits,
//                       RecalibrateBits, WaitingBits, CheckingBits,
//                       PendingBits, BarrelBits, SamplingCallback, OnReset's
//                       recalibrated
//
// __PADSpec at 0x8042CD00 sits just past this unit's .sbss run, so it lives in
// its own unit (the SDK keeps it in Padspec.c); __PADFixBits at 0x8042CF20 is
// further away still. Both are externs here.
//
// DoReset, PADEnable and PADDisable exist only inlined into their callers, and
// PADSync exists only inlined into OnReset; they carry the inline keyword and
// the unit builds with -inline noauto (see configure.py), which reproduces
// exactly that - no standalone bodies, calls kept everywhere else. The public
// functions the game never calls - PADSetSamplingRate, PADControlAllMotors,
// PADGetType, PADSetAnalogMode, __PADDisableXPatch, __PADDisableRumble,
// PADIsBarrel - were emitted but dropped by the original linker; they are
// carried here in the SDK's order with bodies following the SDK as seen in
// other decompilations, and have no bytes in this binary to check against.
// Surviving functions are in the order the original emits them.

// Channel status, ten data bytes plus the error code.
typedef struct PADStatus {
	u16 button;      // 0x0
	s8 stickX;       // 0x2
	s8 stickY;       // 0x3
	s8 substickX;    // 0x4
	s8 substickY;    // 0x5
	u8 triggerLeft;  // 0x6
	u8 triggerRight; // 0x7
	u8 analogA;      // 0x8
	u8 analogB;      // 0x9
	s8 err;          // 0xA
	u8 pad;          // 0xB
} PADStatus;         // 0xC

typedef void (*PADSamplingCallback)(void);

#define PAD_MAX_CONTROLLERS 4

#define PAD_ERR_NONE          0
#define PAD_ERR_NO_CONTROLLER -1
#define PAD_ERR_NOT_READY     -2
#define PAD_ERR_TRANSFER      -3

#define PAD_BUTTON_A     0x0100
#define PAD_BUTTON_B     0x0200
#define PAD_BUTTON_X     0x0400
#define PAD_BUTTON_Y     0x0800
#define PAD_BUTTON_START 0x1000
#define PAD_TRIGGER_L    0x0040
#define PAD_TRIGGER_R    0x0020

#define PAD_CHAN0_BIT 0x80000000u
#define PAD_CHAN1_BIT 0x40000000u
#define PAD_CHAN2_BIT 0x20000000u
#define PAD_CHAN3_BIT 0x10000000u

#define PAD_MOTOR_STOP      0
#define PAD_MOTOR_RUMBLE    1
#define PAD_MOTOR_STOP_HARD 2

#define PAD_SPEC_0 0
#define PAD_SPEC_1 1
#define PAD_SPEC_2 2
#define PAD_SPEC_3 3
#define PAD_SPEC_4 4
#define PAD_SPEC_5 5

// SI device type bits, as the si library reports them.
#define SI_MAX_CHAN           4
#define SI_TYPE_MASK          0x18000000u
#define SI_TYPE_GC            0x08000000u
#define SI_GC_WIRELESS        0x80000000u
#define SI_GC_NOMOTOR         0x20000000u
#define SI_GC_STANDARD        0x01000000u
#define SI_WIRELESS_RECEIVED  0x40000000u
#define SI_WIRELESS_IR        0x04000000u
#define SI_WIRELESS_FIX_ID    0x00100000u
#define SI_WIRELESS_CONT_MASK 0x00080000u
#define SI_WIRELESS_LITE      0x00040000u
#define SI_GC_CONTROLLER      (SI_TYPE_GC | SI_GC_STANDARD)
#define SI_ERROR_NO_RESPONSE  0x0008

// The low-memory words the boot code and this library share: the wireless pad
// fix id at 0x800030E0, and a flags byte at 0x800030E3 carrying the
// recalibration disable bit 0x40 and the rumble disable bit 0x20. Absolute
// address declarations so the compiler treats them as named variables (the
// names are ours; the addresses are what the code proves).
u16 __OSWirelessPadFixMode : 0x800030E0;
u8 __OSWirelessPadFlags : 0x800030E3;

// The si library, by the names the symbol map carries.
extern BOOL SIBusy(void);
extern BOOL SIIsChanBusy(s32 chan);
extern u32 SIGetStatus(s32 chan);
extern void SISetCommand(s32 chan, u32 command);
extern void SITransferCommands(void);
extern u32 SIEnablePolling(u32 poll);
extern u32 SIDisablePolling(u32 poll);
extern BOOL SIGetResponse(s32 chan, void* data);
extern u32 SIGetType(s32 chan);
extern u32 SIGetTypeAsync(s32 chan, void (*callback)(s32, u32));
extern BOOL SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes,
    void (*callback)(s32, u32, OSContext*), OSTime delay);
extern BOOL SIRegisterPollingHandler(void (*handler)(s16, OSContext*));
extern BOOL SIUnregisterPollingHandler(void (*handler)(s16, OSContext*));
extern void SIRefreshSamplingRate(void);
extern void SISetSamplingRate(u32 msec);

extern void OSRegisterVersion(const char* version);
extern void OSRegisterResetFunction(void* info);
extern void OSSetWirelessID(s32 chan, u16 id);
extern OSTime OSGetTime(void);
extern void* memset(void* dst, int val, u32 n);

extern u32 __PADSpec;
extern u32 __PADFixBits;

// The public entry points defined below, for the calls that happen before the
// definitions.
BOOL PADReset(u32 mask);
BOOL PADRecalibrate(u32 mask);
void PADSetSpec(u32 spec);
inline BOOL PADSync(void);
PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback);

// .sdata and .sbss, in address order.
static char* __PADVersion = "<< Dolphin SDK - PAD\trelease build: Aug  6 2003 04:30:02 (0x2301) >>";

// signed long, not s32: this repo types s32 as int, but the SDK's s32 was a
// long, and MWCC's register allocator orders long-typed temporaries
// differently. With int the ResettingBits/ResettingChan pair inside every
// inlined DoReset comes out register-swapped; with long it matches the
// original byte for byte.
static signed long ResettingChan = 32;
static u32 XPatchBits            = PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT;
static u32 AnalogMode            = 0x00000300;
static u32 Spec                  = PAD_SPEC_5;

static BOOL Initialized;
static u32 EnabledBits;
static u32 ResettingBits;
static u32 RecalibrateBits;
static u32 WaitingBits;
static u32 CheckingBits;
static u32 PendingBits;
// unsigned long, not u32, for the same reason ResettingChan is signed long:
// with an int-typed BarrelBits the scheduler hoists the Origin address
// materialization above the BarrelBits store in SPEC2_MakeStatus's barrel
// path; long-typed it keeps the original's order and the function is
// byte-identical.
static unsigned long BarrelBits;

// .bss, in address order. cmdFixDevice below sits right after Origin, which
// is why PADTypeAndStatusCallback reaches all three arrays off one base
// register.
static u32 Type[SI_MAX_CHAN];
static PADStatus Origin[PAD_MAX_CONTROLLERS];

// Forward declarations for everything referenced before its body.
static void PADTypeAndStatusCallback(s32 chan, u32 type);
static inline void DoReset(void);
static inline void PADEnable(s32 chan);
static inline void PADDisable(s32 chan);
static void UpdateOrigin(s32 chan);
static void PADOriginCallback(s32 chan, u32 error, OSContext* context);
static void PADOriginUpdateCallback(s32 chan, u32 error, OSContext* context);
static void PADProbeCallback(s32 chan, u32 error, OSContext* context);
static void PADReceiveCheckCallback(s32 chan, u32 type);
static void SPEC0_MakeStatus(s32 chan, PADStatus* status, u32 data[2]);
static void SPEC1_MakeStatus(s32 chan, PADStatus* status, u32 data[2]);
static inline s8 ClampS8(s8 var, s8 org);
static inline u8 ClampU8(u8 var, u8 org);
static void SPEC2_MakeStatus(s32 chan, PADStatus* status, u32 data[2]);
static BOOL OnReset(BOOL final);
static inline void __PADDisableXPatch(void);
static inline BOOL __PADDisableRumble(BOOL disable);

static void (*MakeStatus)(s32 chan, PADStatus* status, u32 data[2]) = SPEC2_MakeStatus;

static u8 cmdReadOrigin   = 0x41;
static u8 cmdCalibrate[3] = { 0x42, 0x00, 0x00 };
static u32 cmdFixDevice[SI_MAX_CHAN];

typedef struct OSResetFunctionInfo {
	void* func;                       // 0x00
	u32 priority;                     // 0x04
	struct OSResetFunctionInfo* next; // 0x08
	struct OSResetFunctionInfo* prev; // 0x0C
} OSResetFunctionInfo;                // 0x10

// Read off the disc: 801df4f8 0000007f 00000000 00000000.
static OSResetFunctionInfo ResetFunctionInfo = { (void*)OnReset, 127, NULL, NULL };

static inline void PADEnable(s32 chan)
{
	u32 cmd;
	u32 chanBit;
	u32 data[2];

	chanBit = PAD_CHAN0_BIT >> chan;
	EnabledBits |= chanBit;
	SIGetResponse(chan, data);
	cmd = (0x40 << 16) | AnalogMode;
	SISetCommand(chan, cmd);
	SIEnablePolling(EnabledBits);
}

static inline void PADDisable(s32 chan)
{
	BOOL enabled;
	u32 chanBit;

	enabled = OSDisableInterrupts();
	chanBit = PAD_CHAN0_BIT >> chan;
	SIDisablePolling(chanBit);
	EnabledBits &= ~chanBit;
	WaitingBits &= ~chanBit;
	CheckingBits &= ~chanBit;
	PendingBits &= ~chanBit;
	BarrelBits &= ~chanBit;
	OSSetWirelessID(chan, 0);
	OSRestoreInterrupts(enabled);
}

static inline void DoReset(void)
{
	u32 chanBit;

	ResettingChan = __cntlzw(ResettingBits);
	if (ResettingChan != 32) {
		chanBit = PAD_CHAN0_BIT >> ResettingChan;
		ResettingBits &= ~chanBit;

		memset(&Origin[ResettingChan], 0, sizeof(PADStatus));
		SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
	}
}

static void UpdateOrigin(s32 chan)
{
	PADStatus* origin;
	u32 chanBit;

	origin  = &Origin[chan];
	chanBit = PAD_CHAN0_BIT >> chan;
	switch (AnalogMode & 0x00000700) {
		case 0x00000000:
		case 0x00000500:
		case 0x00000600:
		case 0x00000700:
			origin->triggerLeft &= ~15;
			origin->triggerRight &= ~15;
			origin->analogA &= ~15;
			origin->analogB &= ~15;
			break;
		case 0x00000100:
			origin->substickX &= ~15;
			origin->substickY &= ~15;
			origin->analogA &= ~15;
			origin->analogB &= ~15;
			break;
		case 0x00000200:
			origin->substickX &= ~15;
			origin->substickY &= ~15;
			origin->triggerLeft &= ~15;
			origin->triggerRight &= ~15;
			break;
		case 0x00000300:
		case 0x00000400:
			break;
	}

	origin->stickX -= 128;
	origin->stickY -= 128;
	origin->substickX -= 128;
	origin->substickY -= 128;

	if ((XPatchBits & chanBit) && 64 < origin->stickX
	    && (SIGetType(chan) & 0xFFFF0000) == SI_GC_CONTROLLER) {
		origin->stickX = 0;
	}
}

static void PADOriginCallback(s32 chan, u32 error, OSContext* context)
{
	if (!(error & 0x0F)) {
		UpdateOrigin(ResettingChan);
		PADEnable(ResettingChan);
	}
	DoReset();
}

static void PADOriginUpdateCallback(s32 chan, u32 error, OSContext* context)
{
	if (!(EnabledBits & (PAD_CHAN0_BIT >> chan))) {
		return;
	}

	if (!(error & 0x0F)) {
		UpdateOrigin(chan);
	}
	if (error & SI_ERROR_NO_RESPONSE) {
		PADDisable(chan);
	}
}

static void PADProbeCallback(s32 chan, u32 error, OSContext* context)
{
	if (!(error & 0x0F)) {
		PADEnable(ResettingChan);
		WaitingBits |= PAD_CHAN0_BIT >> ResettingChan;
	}
	DoReset();
}

static void PADTypeAndStatusCallback(s32 chan, u32 type)
{
	u32 chanBit;
	u32 recalibrate;
	u32 error;
	BOOL fix;

	fix     = TRUE;
	chanBit = PAD_CHAN0_BIT >> ResettingChan;

	recalibrate = RecalibrateBits & chanBit;
	RecalibrateBits &= ~chanBit;

	error = type & 0x0F;
	if (error) {
		DoReset();
		return;
	}

	Type[ResettingChan] = type &= ~0xFF;

	if ((type & SI_TYPE_MASK) != SI_TYPE_GC || !(type & SI_GC_STANDARD)) {
		DoReset();
		return;
	}

	if (Spec < PAD_SPEC_2) {
		PADEnable(ResettingChan);
		DoReset();
		return;
	}

	if (!(type & SI_GC_WIRELESS) || (type & SI_WIRELESS_IR)) {
		if (recalibrate) {
			fix = SITransfer(
			    ResettingChan, &cmdCalibrate, 3, &Origin[ResettingChan], 10, PADOriginCallback, 0);
		} else {
			fix = SITransfer(
			    ResettingChan, &cmdReadOrigin, 1, &Origin[ResettingChan], 10, PADOriginCallback, 0);
		}
	} else if ((type & SI_WIRELESS_FIX_ID) && !(type & SI_WIRELESS_CONT_MASK)
	    && !(type & SI_WIRELESS_LITE)) {
		if (type & SI_WIRELESS_RECEIVED) {
			fix = SITransfer(
			    ResettingChan, &cmdReadOrigin, 1, &Origin[ResettingChan], 10, PADOriginCallback, 0);
		} else {
			fix = SITransfer(ResettingChan, &cmdFixDevice[ResettingChan], 3, &Origin[ResettingChan],
			    8, PADProbeCallback, 0);
		}
	}

	if (fix) {
		return;
	}

	PendingBits |= chanBit;
	DoReset();
}

static void PADReceiveCheckCallback(s32 chan, u32 type)
{
	u32 error;
	u32 chanBit;

	chanBit = PAD_CHAN0_BIT >> chan;

	if (EnabledBits & chanBit) {
		error = type & 0xFF;
		type &= ~0xFF;

		WaitingBits &= ~chanBit;
		CheckingBits &= ~chanBit;

		if (!(error & 0x0F) && (type & SI_GC_WIRELESS) && (type & SI_WIRELESS_FIX_ID)
		    && (type & SI_WIRELESS_RECEIVED) && !(type & SI_WIRELESS_IR)
		    && !(type & SI_WIRELESS_CONT_MASK) && !(type & SI_WIRELESS_LITE)) {
			SITransfer(chan, &cmdReadOrigin, 1, &Origin[chan], 10, PADOriginUpdateCallback, 0);
		} else {
			PADDisable(chan);
		}
	}
}

BOOL PADReset(u32 mask)
{
	BOOL enabled;
	u32 disableBits;

	enabled = OSDisableInterrupts();

	mask |= PendingBits;
	PendingBits = 0;
	mask &= ~(WaitingBits | CheckingBits);
	ResettingBits |= mask;
	disableBits = ResettingBits & EnabledBits;
	EnabledBits &= ~mask;
	BarrelBits &= ~mask;

	if (Spec == PAD_SPEC_4) {
		RecalibrateBits |= mask;
	}

	SIDisablePolling(disableBits);
	if (ResettingChan == 32) {
		DoReset();
	}
	OSRestoreInterrupts(enabled);
	return TRUE;
}

BOOL PADRecalibrate(u32 mask)
{
	BOOL enabled;
	u32 disableBits;

	enabled = OSDisableInterrupts();

	mask |= PendingBits;
	PendingBits = 0;
	mask &= ~(WaitingBits | CheckingBits);
	ResettingBits |= mask;
	disableBits = ResettingBits & EnabledBits;
	EnabledBits &= ~mask;
	BarrelBits &= ~mask;

	if (!(__OSWirelessPadFlags & 0x40)) {
		RecalibrateBits |= mask;
	}

	SIDisablePolling(disableBits);
	if (ResettingChan == 32) {
		DoReset();
	}
	OSRestoreInterrupts(enabled);
	return TRUE;
}

BOOL PADInit(void)
{
	s32 chan;

	if (Initialized) {
		return TRUE;
	}

	OSRegisterVersion(__PADVersion);

	if (__PADSpec) {
		PADSetSpec(__PADSpec);
	}

	Initialized = TRUE;

	if (__PADFixBits != 0) {
		OSTime time            = OSGetTime();
		__OSWirelessPadFixMode = (u16)((((time) & 0xffff) + ((time >> 16) & 0xffff)
		                                   + ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff))
		    & 0x3fff);
		RecalibrateBits        = PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT;
	}

	for (chan = 0; chan < SI_MAX_CHAN; ++chan) {
		cmdFixDevice[chan]
		    = 0x4D000000 | (chan << 22) | (((u32)__OSWirelessPadFixMode & 0x3fffu) << 8);
	}

	SIRefreshSamplingRate();
	OSRegisterResetFunction(&ResetFunctionInfo);

	return PADReset(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
}

u32 PADRead(PADStatus* status)
{
	BOOL enabled;
	s32 chan;
	u32 data[2];
	u32 chanBit;
	u32 sr;
	int chanShift;
	u32 motor;

	enabled = OSDisableInterrupts();

	motor = 0;
	for (chan = 0; chan < PAD_MAX_CONTROLLERS; ++chan, ++status) {
		chanBit = PAD_CHAN0_BIT >> chan;

		if (PendingBits & chanBit) {
			PADReset(0);
			status->err = PAD_ERR_NOT_READY;
			memset(status, 0, 10); // up to err
			continue;
		}

		if ((ResettingBits & chanBit) || ResettingChan == chan) {
			status->err = PAD_ERR_NOT_READY;
			memset(status, 0, 10); // up to err
			continue;
		}

		if (!(EnabledBits & chanBit)) {
			status->err = PAD_ERR_NO_CONTROLLER;
			memset(status, 0, 10); // up to err
			continue;
		}

		if (SIIsChanBusy(chan)) {
			status->err = PAD_ERR_TRANSFER;
			memset(status, 0, 10); // up to err
			continue;
		}

		sr = SIGetStatus(chan);
		if (sr & SI_ERROR_NO_RESPONSE) {
			SIGetResponse(chan, data);
			if (WaitingBits & chanBit) {
				status->err = PAD_ERR_NONE;
				memset(status, 0, 10); // up to err
				if (!(CheckingBits & chanBit)) {
					CheckingBits |= chanBit;
					SIGetTypeAsync(chan, PADReceiveCheckCallback);
				}
				continue;
			}
			PADDisable(chan);
			status->err = PAD_ERR_NO_CONTROLLER;
			memset(status, 0, 10); // up to err
			continue;
		}

		if (!(SIGetType(chan) & SI_GC_NOMOTOR)) {
			motor |= chanBit;
		}

		if (!SIGetResponse(chan, data)) {
			status->err = PAD_ERR_TRANSFER;
			memset(status, 0, 10); // up to err
			continue;
		}

		if (data[0] & 0x80000000) {
			status->err = PAD_ERR_TRANSFER;
			memset(status, 0, 10); // up to err
			continue;
		}

		MakeStatus(chan, status, data);

		if (status->button & 0x2000) {
			status->err = PAD_ERR_TRANSFER;
			memset(status, 0, 10); // up to err
			SITransfer(chan, &cmdReadOrigin, 1, &Origin[chan], 10, PADOriginUpdateCallback, 0);
			continue;
		}

		status->err = PAD_ERR_NONE;
		status->button &= ~0x0080;
	}
	OSRestoreInterrupts(enabled);
	return motor;
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline void PADSetSamplingRate(u32 msec)
{
	SISetSamplingRate(msec);
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline void PADControlAllMotors(const u32* commandArray)
{
	BOOL enabled;
	int chan;
	u32 command;
	BOOL commit;
	u32 chanBit;

	enabled = OSDisableInterrupts();
	commit  = FALSE;

	for (chan = 0; chan < SI_MAX_CHAN; chan++, commandArray++) {
		chanBit = PAD_CHAN0_BIT >> chan;
		if ((EnabledBits & chanBit) && !(SIGetType(chan) & SI_GC_NOMOTOR)) {
			command = *commandArray;
			if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD) {
				command = PAD_MOTOR_STOP;
			}
			if (__OSWirelessPadFlags & 0x20) {
				command = PAD_MOTOR_STOP;
			}
			SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & 0x3));
			commit = TRUE;
		}
	}

	if (commit) {
		SITransferCommands();
	}

	OSRestoreInterrupts(enabled);
}

void PADControlMotor(s32 chan, u32 command)
{
	BOOL enabled;
	u32 chanBit;

	enabled = OSDisableInterrupts();

	chanBit = PAD_CHAN0_BIT >> chan;
	if ((EnabledBits & chanBit) && !(SIGetType(chan) & SI_GC_NOMOTOR)) {
		if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD) {
			command = PAD_MOTOR_STOP;
		}
		if (__OSWirelessPadFlags & 0x20) {
			command = PAD_MOTOR_STOP;
		}
		SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & 0x3));
		SITransferCommands();
	}
	OSRestoreInterrupts(enabled);
}

void PADSetSpec(u32 spec)
{
	__PADSpec = 0;

	switch (spec) {
		case PAD_SPEC_0:
			MakeStatus = SPEC0_MakeStatus;
			break;
		case PAD_SPEC_1:
			MakeStatus = SPEC1_MakeStatus;
			break;
		case PAD_SPEC_2:
		case PAD_SPEC_3:
		case PAD_SPEC_4:
		case PAD_SPEC_5:
			MakeStatus = SPEC2_MakeStatus;
			break;
	}

	Spec = spec;
}

static void SPEC0_MakeStatus(s32 chan, PADStatus* status, u32 data[2])
{
	status->button = 0;
	status->button |= ((data[0] >> 16) & 0x0008) ? PAD_BUTTON_A : 0;
	status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_B : 0;
	status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_X : 0;
	status->button |= ((data[0] >> 16) & 0x0001) ? PAD_BUTTON_Y : 0;
	status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_START : 0;
	status->stickX       = (s8)(data[1] >> 16);
	status->stickY       = (s8)(data[1] >> 24);
	status->substickX    = (s8)(data[1] >> 0);
	status->substickY    = (s8)(data[1] >> 8);
	status->triggerLeft  = (u8)(data[0] >> 8);
	status->triggerRight = (u8)(data[0] >> 0);
	status->analogA      = 0;
	status->analogB      = 0;
	if (170 <= status->triggerLeft) {
		status->button |= PAD_TRIGGER_L;
	}
	if (170 <= status->triggerRight) {
		status->button |= PAD_TRIGGER_R;
	}
	status->stickX -= 128;
	status->stickY -= 128;
	status->substickX -= 128;
	status->substickY -= 128;
}

static void SPEC1_MakeStatus(s32 chan, PADStatus* status, u32 data[2])
{
	status->button = 0;
	status->button |= ((data[0] >> 16) & 0x0080) ? PAD_BUTTON_A : 0;
	status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_B : 0;
	status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_X : 0;
	status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_Y : 0;
	status->button |= ((data[0] >> 16) & 0x0200) ? PAD_BUTTON_START : 0;
	status->stickX       = (s8)(data[1] >> 16);
	status->stickY       = (s8)(data[1] >> 24);
	status->substickX    = (s8)(data[1] >> 0);
	status->substickY    = (s8)(data[1] >> 8);
	status->triggerLeft  = (u8)(data[0] >> 8);
	status->triggerRight = (u8)(data[0] >> 0);
	status->analogA      = 0;
	status->analogB      = 0;
	if (170 <= status->triggerLeft) {
		status->button |= PAD_TRIGGER_L;
	}
	if (170 <= status->triggerRight) {
		status->button |= PAD_TRIGGER_R;
	}
	status->stickX -= 128;
	status->stickY -= 128;
	status->substickX -= 128;
	status->substickY -= 128;
}

static inline s8 ClampS8(s8 var, s8 org)
{
	if (0 < org) {
		s8 min = (s8)(-128 + org);
		if (var < min) {
			var = min;
		}
	} else if (org < 0) {
		s8 max = (s8)(127 + org);
		if (max < var) {
			var = max;
		}
	}
	return var -= org;
}

static inline u8 ClampU8(u8 var, u8 org)
{
	if (var < org) {
		var = org;
	}
	return var -= org;
}

static void SPEC2_MakeStatus(s32 chan, PADStatus* status, u32 data[2])
{
	PADStatus* origin;

	status->button = (u16)((data[0] >> 16) & 0x3FFF);
	status->stickX = (s8)(data[0] >> 8);
	status->stickY = (s8)(data[0]);

	switch (AnalogMode & 0x00000700) {
		case 0x00000000:
		case 0x00000500:
		case 0x00000600:
		case 0x00000700:
			status->substickX    = (s8)(data[1] >> 24);
			status->substickY    = (s8)(data[1] >> 16);
			status->triggerLeft  = (u8)(((data[1] >> 12) & 0x0f) << 4);
			status->triggerRight = (u8)(((data[1] >> 8) & 0x0f) << 4);
			status->analogA      = (u8)(((data[1] >> 4) & 0x0f) << 4);
			status->analogB      = (u8)(((data[1] >> 0) & 0x0f) << 4);
			break;
		case 0x00000100:
			status->substickX    = (s8)(((data[1] >> 28) & 0x0f) << 4);
			status->substickY    = (s8)(((data[1] >> 24) & 0x0f) << 4);
			status->triggerLeft  = (u8)(data[1] >> 16);
			status->triggerRight = (u8)(data[1] >> 8);
			status->analogA      = (u8)(((data[1] >> 4) & 0x0f) << 4);
			status->analogB      = (u8)(((data[1] >> 0) & 0x0f) << 4);
			break;
		case 0x00000200:
			status->substickX    = (s8)(((data[1] >> 28) & 0x0f) << 4);
			status->substickY    = (s8)(((data[1] >> 24) & 0x0f) << 4);
			status->triggerLeft  = (u8)(((data[1] >> 20) & 0x0f) << 4);
			status->triggerRight = (u8)(((data[1] >> 16) & 0x0f) << 4);
			status->analogA      = (u8)(data[1] >> 8);
			status->analogB      = (u8)(data[1] >> 0);
			break;
		case 0x00000300:
			status->substickX    = (s8)(data[1] >> 24);
			status->substickY    = (s8)(data[1] >> 16);
			status->triggerLeft  = (u8)(data[1] >> 8);
			status->triggerRight = (u8)(data[1] >> 0);
			status->analogA      = 0;
			status->analogB      = 0;
			break;
		case 0x00000400:
			status->substickX    = (s8)(data[1] >> 24);
			status->substickY    = (s8)(data[1] >> 16);
			status->triggerLeft  = 0;
			status->triggerRight = 0;
			status->analogA      = (u8)(data[1] >> 8);
			status->analogB      = (u8)(data[1] >> 0);
			break;
	}

	status->stickX -= 128;
	status->stickY -= 128;
	status->substickX -= 128;
	status->substickY -= 128;

	if ((Type[chan] & 0xFFFF0000) == SI_GC_CONTROLLER && ((status->button & 0x0080) ^ 0x0080)) {
		BarrelBits |= PAD_CHAN0_BIT >> chan;
		status->stickX    = 0;
		status->stickY    = 0;
		status->substickX = 0;
		status->substickY = 0;
		return;
	} else {
		BarrelBits &= ~(PAD_CHAN0_BIT >> chan);
	}

	origin               = &Origin[chan];
	status->stickX       = ClampS8(status->stickX, origin->stickX);
	status->stickY       = ClampS8(status->stickY, origin->stickY);
	status->substickX    = ClampS8(status->substickX, origin->substickX);
	status->substickY    = ClampS8(status->substickY, origin->substickY);
	status->triggerLeft  = ClampU8(status->triggerLeft, origin->triggerLeft);
	status->triggerRight = ClampU8(status->triggerRight, origin->triggerRight);
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline int PADGetType(s32 chan, u32* type)
{
	u32 chanBit;

	*type   = SIGetType(chan);
	chanBit = PAD_CHAN0_BIT >> chan;
	if ((ResettingBits & chanBit) || ResettingChan == chan || !(EnabledBits & chanBit)) {
		return FALSE;
	}
	return TRUE;
}

// No standalone body exists in the binary or in this compilation: OnReset
// gets it inlined and nothing else refers to it.
inline BOOL PADSync(void)
{
	return ResettingBits == 0 && ResettingChan == 32 && !SIBusy();
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline void PADSetAnalogMode(u32 mode)
{
	BOOL enabled;
	u32 mask;

	enabled    = OSDisableInterrupts();
	AnalogMode = mode << 8;
	mask       = EnabledBits;

	EnabledBits &= ~mask;
	WaitingBits &= ~mask;
	CheckingBits &= ~mask;

	SIDisablePolling(mask);
	OSRestoreInterrupts(enabled);
}

static PADSamplingCallback SamplingCallback;

static BOOL OnReset(BOOL final)
{
	BOOL sync;
	static BOOL recalibrated = FALSE;

	if (SamplingCallback) {
		PADSetSamplingCallback(NULL);
	}

	if (!final) {
		sync = PADSync();

		if (!recalibrated && sync) {
			recalibrated
			    = PADRecalibrate(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
			return FALSE;
		}
		return sync;
	} else {
		recalibrated = FALSE;
	}

	return TRUE;
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline void __PADDisableXPatch(void)
{
	XPatchBits = 0;
}

static void SamplingHandler(s16 interrupt, OSContext* context)
{
	OSContext exceptionContext;

	if (SamplingCallback) {
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(&exceptionContext);

		SamplingCallback();

		OSClearContext(&exceptionContext);
		OSSetCurrentContext(context);
	}
}

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback)
{
	PADSamplingCallback prev;

	prev             = SamplingCallback;
	SamplingCallback = callback;
	if (callback) {
		SIRegisterPollingHandler(SamplingHandler);
	} else {
		SIUnregisterPollingHandler(SamplingHandler);
	}
	return prev;
}

BOOL __PADDisableRecalibration(BOOL disable)
{
	BOOL enabled;
	BOOL prev;

	enabled = OSDisableInterrupts();

	prev = (__OSWirelessPadFlags & 0x40) ? TRUE : FALSE;
	__OSWirelessPadFlags &= ~0x40;
	if (disable) {
		__OSWirelessPadFlags |= 0x40;
	}

	OSRestoreInterrupts(enabled);
	return prev;
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline BOOL __PADDisableRumble(BOOL disable)
{
	BOOL enabled;
	BOOL prev;

	enabled = OSDisableInterrupts();

	prev = (__OSWirelessPadFlags & 0x20) ? TRUE : FALSE;
	__OSWirelessPadFlags &= ~0x20;
	if (disable) {
		__OSWirelessPadFlags |= 0x20;
	}

	OSRestoreInterrupts(enabled);
	return prev;
}

// Not in the binary: nothing references it, so the original linker dropped it.
static inline BOOL PADIsBarrel(s32 chan)
{
	if (chan < 0 || chan >= PAD_MAX_CONTROLLERS) {
		return FALSE;
	}

	if (BarrelBits & (PAD_CHAN0_BIT >> chan)) {
		return TRUE;
	}

	return FALSE;
}
