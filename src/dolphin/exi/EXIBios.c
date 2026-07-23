#include "types.h"
#include "dolphin/os.h"

// The external interface bus driver.
//
// The translation unit runs from SetExiInterruptMask at 0x801FA418 to the end
// of EXIGetID at 0x801FBDF4. The unit was previously split at EXIImm; the
// 0xF4 bytes before it are SetExiInterruptMask, which is the first function of
// the SDK's EXIBios.c, so the split now starts there. After the unit is
// __OSEnableBarnacle, which belongs to OS.
//
// The public functions keep their dtk names until renamed with evidence, but
// their SDK identities are clear from structure: fn_801FA768 is EXIImmEx,
// fn_801FAB88 is EXISetExiCallback, fn_801FAD78 is EXIProbe, fn_801FADF8 is
// EXIProbeEx, fn_801FAEAC is EXIAttach, fn_801FAFB8 is EXIDetach and
// fn_801FBA04 is EXIGetState.
//
// CompleteTransfer and __EXIAttach exist in the source but not in the binary:
// each is a small static defined before every caller, so the compiler inlines
// every call and emits no standalone body. That is why EXISync and
// TCIntrruptHandler share their copy-out loop, and why fn_801FAEAC and
// EXIGetID share their attach sequence.
//
// EXISync carries a Sonic Heroes addition: after a transfer completes it
// cross-checks the device identifier against a list and a halfword at
// physical 0x30E6 on development hardware. The constants are kept as hex; what
// qualifies a device is not established beyond what the code does.
//
// Two codegen settings are needed here and neither is a workaround for C that
// would not match otherwise.
//
// The unit is built with -opt noschedule. Every function in it came out with
// the right instructions in the wrong order until the scheduler was turned
// off, which took the file from 71% to 100% on twenty-two of its twenty-three
// functions in one step. That is the expected setting for a driver that walks
// a volatile register block: the SDK has no reason to let the scheduler move
// hardware accesses around, and nothing else in the sweep came close.
//
// EXIImm additionally sits between #pragma opt_propagation off and on. Its
// byte packing loop is entered with a guard the original spells as a compare
// of the counter against the length, while constant propagation folds ours to
// a test of the length alone because it can see the counter is still zero. The
// two instructions that produced were the last difference in the file. Eight
// spellings of the loop were measured first and none of them stopped the fold,
// so the pragma is what pins it, kept around this one function because turning
// propagation off for the whole unit breaks six others.

// The register block gives each of the three channels five words: status at 0,
// then the DMA address, the length, the control word and the immediate data.
// This is the CodeWarrior absolute-address declaration the SDK itself uses.
#ifdef __MWERKS__
volatile u32 __EXIRegs[] : 0xCC006800;
#else
extern volatile u32 __EXIRegs[];
#endif
#define EXI_REGS       __EXIRegs
#define EXI_CHAN_WORDS 5

// Status register bits. The mask is everything that has to survive a write,
// the three flags below are write-one-to-clear interrupt causes.
#define EXI_CSR_KEEP 0x7F5
#define EXI_CSR_EXI  0x0002
#define EXI_CSR_TC   0x0008
#define EXI_CSR_EXT  0x0800

typedef void (*EXICallback)(s32 chan, void* context);

// Physical address zero is mirrored at 0x80000000 through the cache.
#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + 0x80000000))

// One control block per channel, 0x40 bytes each, in .bss. Field offsets are
// fixed by the code below; the layout is the SDK's.
typedef struct EXIControl {
	EXICallback exiCallback; // 0x00
	EXICallback tcCallback;  // 0x04
	EXICallback extCallback; // 0x08
	volatile u32 state;      // 0x0C
	int immLen;              // 0x10
	u8* immBuf;              // 0x14
	u32 dev;                 // 0x18
	u32 id;                  // 0x1C
	s32 idTime;              // 0x20
	int items;               // 0x24
	struct {
		u32 dev;              // 0x00
		EXICallback callback; // 0x04
	} queue[3];               // 0x28
} EXIControl;                 // 0x40

#define EXI_STATE_DMA      0x1
#define EXI_STATE_IMM      0x2
#define EXI_STATE_BUSY     (EXI_STATE_DMA | EXI_STATE_IMM)
#define EXI_STATE_SELECTED 0x4
#define EXI_STATE_ATTACHED 0x8
#define EXI_STATE_LOCKED   0x10

// EXI transfer types as passed in the control word.
#define EXI_READ  0
#define EXI_WRITE 1

extern __OSInterruptHandler __OSGetInterruptHandler(s16 interrupt);
extern OSTime OSGetTime(void);
extern u32 OSGetConsoleType(void);
extern void OSRegisterVersion(const char* version);
extern void __OSEnableBarnacle(s32 chan, u32 dev);
extern void* memmove(void* dst, const void* src, u32 n);

// Returns a device family byte; 0xFF means nothing to check. The function
// lives past the end of OS.c and has no name yet.
extern u32 __OSGetDIConfig(void);

// Set while the IPL menu is running.
extern BOOL __OSInIPL;

// Pointer to the SDK version string, registered on init.
extern char* __EXIVersion;

BOOL EXIImm(s32 chan, void* buf, s32 len, u32 type, EXICallback callback);
BOOL EXISync(s32 chan);
u32 EXIClearInterrupts(s32 chan, BOOL exi, BOOL tc, BOOL ext);
BOOL EXISelect(s32 chan, u32 dev, u32 freq);
BOOL EXIDeselect(s32 chan);
BOOL EXILock(s32 chan, u32 dev, EXICallback unlockedCallback);
BOOL EXIUnlock(s32 chan);
s32 EXIGetID(s32 chan, u32 dev, u32* id);
BOOL fn_801FAD78(s32 chan);
static BOOL __EXIProbe(s32 chan);
static void EXIIntrruptHandler(s16 interrupt, OSContext* context);
static void TCIntrruptHandler(s16 interrupt, OSContext* context);
static void EXTIntrruptHandler(s16 interrupt, OSContext* context);
static void UnlockedHandler(s32 chan, void* context);

// One control block per channel. File local in the original; the split owns
// the .bss range so the definition lives here.
static EXIControl Ecb[3];

// The serial port 1 identifier latched by EXIInit, answered from cache by
// EXIGetID. File local, in the unit's .sbss.
static u32 IDSerialPort1;

// Per-channel probe timestamps in low memory, as a CW absolute-address
// array so the base materialises with lis/addi and indexes fold.
#ifdef __MWERKS__
s32 EXIProbeStartTime[3] : 0x800030C0;
#else
extern s32 EXIProbeStartTime[3];
#endif

// Decides whether the channel's own interrupt is worth taking: masked when
// nobody installed a callback or while the channel is locked. Channel 0 gates
// channel 2's line as well, and channel 2 itself is wired to the debugger
// interrupt, which is why it asks for the PI_DEBUG handler.
static void SetExiInterruptMask(s32 chan, EXIControl* exi)
{
	EXIControl* exi2 = &Ecb[2];

	switch (chan) {
		case 0:
			if ((exi->exiCallback == 0 && exi2->exiCallback == 0)
			    || (exi->state & EXI_STATE_LOCKED)) {
				__OSMaskInterrupts(0x410000);
			} else {
				__OSUnmaskInterrupts(0x410000);
			}
			break;
		case 1:
			if (exi->exiCallback == 0 || (exi->state & EXI_STATE_LOCKED)) {
				__OSMaskInterrupts(0x80000);
			} else {
				__OSUnmaskInterrupts(0x80000);
			}
			break;
		case 2:
			if (__OSGetInterruptHandler(0x19) == 0 || (exi->state & EXI_STATE_LOCKED)) {
				__OSMaskInterrupts(0x40);
			} else {
				__OSUnmaskInterrupts(0x40);
			}
			break;
	}
}

// Drains a finished immediate transfer back into the caller's buffer. Inlined
// into every caller, so it has no body in the binary.
static inline void CompleteTransfer(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	u8* buf;
	u32 data;
	int i;
	int len;

	if (exi->state & EXI_STATE_BUSY) {
		if ((exi->state & EXI_STATE_IMM) && (len = exi->immLen) != 0) {
			buf  = exi->immBuf;
			data = EXI_REGS[chan * EXI_CHAN_WORDS + 4];
			for (i = 0; i < len; i++) {
				*buf++ = (u8)(data >> ((3 - i) * 8));
			}
		}
		exi->state &= ~EXI_STATE_BUSY;
	}
}

#pragma opt_propagation off
BOOL EXIImm(s32 chan, void* buf, s32 len, u32 type, EXICallback callback)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if ((exi->state & EXI_STATE_BUSY) || !(exi->state & EXI_STATE_SELECTED)) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->tcCallback = callback;
	if (exi->tcCallback) {
		EXIClearInterrupts(chan, FALSE, TRUE, FALSE);
		__OSUnmaskInterrupts(0x200000U >> (chan * 3));
	}

	exi->state |= EXI_STATE_IMM;

	if (type != EXI_READ) {
		u32 data;
		int i;

		data = 0;
		for (i = 0; i < len; i++) {
			data |= (u32)((u8*)buf)[i] << ((3 - i) * 8);
		}
		EXI_REGS[chan * EXI_CHAN_WORDS + 4] = data;
	}

	exi->immBuf = buf;
	exi->immLen = (type != EXI_WRITE) ? len : 0;

	EXI_REGS[chan * EXI_CHAN_WORDS + 3] = 0x1 | (type << 2) | ((len - 1) << 4);

	OSRestoreInterrupts(enabled);
	return TRUE;
}
#pragma opt_propagation on

// EXIImmEx in the SDK: chops a buffer into four byte immediate transfers.
BOOL fn_801FA768(s32 chan, void* buf, s32 len, u32 mode)
{
	s32 xLen;

	while (len != 0) {
		xLen = (len < 4) ? len : 4;
		if (!EXIImm(chan, buf, xLen, mode, NULL)) {
			return FALSE;
		}
		if (!EXISync(chan)) {
			return FALSE;
		}
		buf = (u8*)buf + xLen;
		len -= xLen;
	}

	return TRUE;
}

BOOL EXIDma(s32 chan, void* buf, s32 len, u32 type, EXICallback callback)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if ((exi->state & EXI_STATE_BUSY) || !(exi->state & EXI_STATE_SELECTED)) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->tcCallback = callback;
	if (exi->tcCallback) {
		EXIClearInterrupts(chan, FALSE, TRUE, FALSE);
		__OSUnmaskInterrupts(0x200000U >> (chan * 3));
	}

	exi->state |= EXI_STATE_DMA;

	EXI_REGS[chan * EXI_CHAN_WORDS + 1] = (u32)buf & 0x03FFFFE0;
	EXI_REGS[chan * EXI_CHAN_WORDS + 2] = (u32)len;
	EXI_REGS[chan * EXI_CHAN_WORDS + 3] = (type << 2) | 0x3;

	OSRestoreInterrupts(enabled);
	return TRUE;
}

BOOL EXISync(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	BOOL ret        = FALSE;
	BOOL enabled;

	while (exi->state & EXI_STATE_SELECTED) {
		if (EXI_REGS[chan * EXI_CHAN_WORDS + 3] & 1) {
			continue;
		}

		enabled = OSDisableInterrupts();
		if (exi->state & EXI_STATE_SELECTED) {
			CompleteTransfer(chan);

			// Sonic Heroes addition: the transfer only counts if the device
			// does not match one of three identifiers on retail hardware, or
			// if the halfword at physical 0x30E6 vouches for it.
			if (__OSGetDIConfig() != 0xFF || (OSGetConsoleType() & 0xF0000000) == 0x20000000
			    || exi->immLen != 4 || (EXI_REGS[chan * EXI_CHAN_WORDS] & 0x70)
			    || (EXI_REGS[chan * EXI_CHAN_WORDS + 4] != 0x01010000
			        && EXI_REGS[chan * EXI_CHAN_WORDS + 4] != 0x05070000
			        && EXI_REGS[chan * EXI_CHAN_WORDS + 4] != 0x04220001)
			    || *(volatile u16*)OSPhysicalToCached(0x30E6) == 0x8200) {
				ret = TRUE;
			}
		}
		OSRestoreInterrupts(enabled);
		break;
	}

	return ret;
}

// Acknowledges whichever of the three interrupt causes the caller names and
// hands back the status word as it was before the write. The causes are write
// one to clear, so the ones not named have to be masked out rather than left
// alone, or acknowledging one would acknowledge all three.
u32 EXIClearInterrupts(s32 chan, BOOL exi, BOOL tc, BOOL ext)
{
	u32 cpr;
	u32 v;

	v   = EXI_REGS[chan * EXI_CHAN_WORDS];
	cpr = v;
	v &= EXI_CSR_KEEP;
	if (exi) {
		v |= EXI_CSR_EXI;
	}
	if (tc) {
		v |= EXI_CSR_TC;
	}
	if (ext) {
		v |= EXI_CSR_EXT;
	}

	EXI_REGS[chan * EXI_CHAN_WORDS] = v;

	return cpr;
}

// EXISetExiCallback in the SDK: swaps in a new callback for the channel's own
// interrupt and hands back the one that was there. Channel 2 has no mask of
// its own, so the mask for channel 0 is what gets recomputed on its behalf.
EXICallback fn_801FAB88(s32 chan, EXICallback exiCallback)
{
	EXIControl* exi = &Ecb[chan];
	EXICallback prev;
	BOOL enabled;

	enabled = OSDisableInterrupts();

	prev             = exi->exiCallback;
	exi->exiCallback = exiCallback;

	if (chan != 2) {
		SetExiInterruptMask(chan, exi);
	} else {
		SetExiInterruptMask(0, &Ecb[0]);
	}

	OSRestoreInterrupts(enabled);

	return prev;
}

// Answers whether something is physically on the channel, debouncing
// insertions with a three tick window measured in hundreds of milliseconds.
static BOOL __EXIProbe(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;
	BOOL prb;
	u32 cpr;
	s32 t;

	if (chan == 2) {
		return TRUE;
	}

	prb     = TRUE;
	enabled = OSDisableInterrupts();
	cpr     = EXI_REGS[chan * EXI_CHAN_WORDS];

	if (!(exi->state & EXI_STATE_ATTACHED)) {
		if (cpr & EXI_CSR_EXT) {
			EXI_REGS[chan * EXI_CHAN_WORDS]
			    = (EXI_REGS[chan * EXI_CHAN_WORDS] & EXI_CSR_KEEP) | EXI_CSR_EXT;
			exi->idTime             = 0;
			EXIProbeStartTime[chan] = 0;
		}
		if (cpr & 0x1000) {
			// Milliseconds over a hundred, plus one so zero means unset.
			t = (s32)(OSGetTime() / ((*(u32*)OSPhysicalToCached(0xF8) / 4) / 1000) / 100) + 1;
			if (EXIProbeStartTime[chan] == 0) {
				EXIProbeStartTime[chan] = t;
			}
			if (t - EXIProbeStartTime[chan] < 3) {
				prb = FALSE;
			}
		} else {
			exi->idTime             = 0;
			EXIProbeStartTime[chan] = 0;
			prb                     = FALSE;
		}
	} else {
		if (!(cpr & 0x1000) || (cpr & EXI_CSR_EXT)) {
			exi->idTime             = 0;
			EXIProbeStartTime[chan] = 0;
			prb                     = FALSE;
		}
	}

	OSRestoreInterrupts(enabled);
	return prb;
}

// EXIProbe in the SDK: answers whether something is attached and identified.
// A probe on its own is not enough: a channel that has never reported an
// identifier gets asked for one, and only a successful answer counts.
BOOL fn_801FAD78(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	BOOL prb;
	u32 id;

	prb = __EXIProbe(chan);
	if (prb && exi->idTime == 0) {
		prb = EXIGetID(chan, 0, &id) ? TRUE : FALSE;
	}
	return prb;
}

// EXIProbeEx in the SDK: three answers instead of two. Zero means a device is
// still settling in its debounce window, minus one means nothing there.
s32 fn_801FADF8(s32 chan)
{
	if (fn_801FAD78(chan)) {
		return 1;
	}
	if (EXIProbeStartTime[chan] != 0) {
		return 0;
	}
	return -1;
}

// Claims the channel's external interrupt for a callback. Inlined into its
// callers, so it has no body in the binary.
static inline BOOL __EXIAttach(s32 chan, EXICallback extCallback)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if ((exi->state & EXI_STATE_ATTACHED) || __EXIProbe(chan) == FALSE) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	EXIClearInterrupts(chan, TRUE, FALSE, FALSE);
	exi->extCallback = extCallback;
	__OSUnmaskInterrupts(0x100000U >> (chan * 3));
	exi->state |= EXI_STATE_ATTACHED;

	OSRestoreInterrupts(enabled);
	return TRUE;
}

// EXIAttach in the SDK.
BOOL fn_801FAEAC(s32 chan, EXICallback extCallback)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;
	BOOL ret;

	fn_801FAD78(chan);

	enabled = OSDisableInterrupts();
	if (exi->idTime == 0) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	ret = __EXIAttach(chan, extCallback);
	OSRestoreInterrupts(enabled);
	return ret;
}

// EXIDetach in the SDK.
BOOL fn_801FAFB8(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if (!(exi->state & EXI_STATE_ATTACHED)) {
		OSRestoreInterrupts(enabled);
		return TRUE;
	}

	if ((exi->state & EXI_STATE_LOCKED) && exi->dev == 0) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->state &= ~EXI_STATE_ATTACHED;
	__OSMaskInterrupts(0x500000U >> (chan * 3));

	OSRestoreInterrupts(enabled);
	return TRUE;
}

BOOL EXISelect(s32 chan, u32 dev, u32 freq)
{
	EXIControl* exi = &Ecb[chan];
	u32 cpr;
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if ((exi->state & EXI_STATE_SELECTED)
	    || (chan != 2
	        && ((dev == 0 && !(exi->state & EXI_STATE_ATTACHED) && !__EXIProbe(chan))
	            || !(exi->state & EXI_STATE_LOCKED) || exi->dev != dev))) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->state |= EXI_STATE_SELECTED;

	cpr = EXI_REGS[chan * EXI_CHAN_WORDS];
	cpr &= 0x405;
	cpr |= ((1 << dev) << 7) | (freq << 4);
	EXI_REGS[chan * EXI_CHAN_WORDS] = cpr;

	if (exi->state & EXI_STATE_ATTACHED) {
		switch (chan) {
			case 0:
				__OSMaskInterrupts(0x100000);
				break;
			case 1:
				__OSMaskInterrupts(0x20000);
				break;
		}
	}

	OSRestoreInterrupts(enabled);
	return TRUE;
}

BOOL EXIDeselect(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	u32 cpr;
	BOOL enabled;

	enabled = OSDisableInterrupts();

	if (!(exi->state & EXI_STATE_SELECTED)) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->state &= ~EXI_STATE_SELECTED;

	cpr                             = EXI_REGS[chan * EXI_CHAN_WORDS];
	EXI_REGS[chan * EXI_CHAN_WORDS] = cpr & 0x405;

	if (exi->state & EXI_STATE_ATTACHED) {
		switch (chan) {
			case 0:
				__OSUnmaskInterrupts(0x100000);
				break;
			case 1:
				__OSUnmaskInterrupts(0x20000);
				break;
		}
	}

	OSRestoreInterrupts(enabled);

	if (chan != 2 && (cpr & 0x80)) {
		if (__EXIProbe(chan)) {
			return TRUE;
		}
		return FALSE;
	}

	return TRUE;
}

static void EXIIntrruptHandler(s16 interrupt, OSContext* context)
{
	s32 chan;
	EXIControl* exi;
	EXICallback callback;
	OSContext exiContext;
	// Dead local: the original frame is 4 bytes wider below the context.
	u32 pad;

	chan = (interrupt - 9) / 3;
	EXIClearInterrupts(chan, TRUE, FALSE, FALSE);

	exi      = &Ecb[chan];
	callback = exi->exiCallback;
	if (callback) {
		OSClearContext(&exiContext);
		OSSetCurrentContext(&exiContext);

		callback(chan, context);

		OSClearContext(&exiContext);
		OSSetCurrentContext(context);
	}
}

static void TCIntrruptHandler(s16 interrupt, OSContext* context)
{
	s32 chan;
	EXIControl* exi;
	EXICallback callback;
	OSContext exiContext;
	// Dead local: the original frame is 4 bytes wider below the context.
	u32 pad;

	chan = (interrupt - 10) / 3;
	exi  = &Ecb[chan];

	__OSMaskInterrupts(0x80000000U >> interrupt);
	EXIClearInterrupts(chan, FALSE, TRUE, FALSE);

	callback = exi->tcCallback;
	if (callback) {
		exi->tcCallback = NULL;

		CompleteTransfer(chan);

		OSClearContext(&exiContext);
		OSSetCurrentContext(&exiContext);

		callback(chan, context);

		OSClearContext(&exiContext);
		OSSetCurrentContext(context);
	}
}

// The external interrupt says a device was inserted or removed. The interrupt
// numbers for the three channels are three apart starting at 0x0B, which is
// where the divide comes from. The callback runs on a context of its own so
// that whatever it does cannot disturb the one that was interrupted.
static void EXTIntrruptHandler(s16 interrupt, OSContext* context)
{
	s32 chan;
	EXIControl* exi;
	EXICallback callback;
	OSContext exiContext;

	chan = (interrupt - 0xB) / 3;
	__OSMaskInterrupts(0x500000U >> (chan * 3));

	exi = &Ecb[chan];

	callback = exi->extCallback;
	exi->state &= ~EXI_STATE_ATTACHED;

	if (callback != NULL) {
		OSClearContext(&exiContext);
		OSSetCurrentContext(&exiContext);

		exi->extCallback = NULL;
		callback(chan, context);

		OSClearContext(&exiContext);
		OSSetCurrentContext(context);
	}
}

void EXIInit(void)
{
	u32 id;

	// Wait until nothing is mid transfer on any channel.
	while ((EXI_REGS[0 * EXI_CHAN_WORDS + 3] & 1) == 1
	    || (EXI_REGS[1 * EXI_CHAN_WORDS + 3] & 1) == 1
	    || (EXI_REGS[2 * EXI_CHAN_WORDS + 3] & 1) == 1) {
	}

	__OSMaskInterrupts(0x7F8000);

	EXI_REGS[0 * EXI_CHAN_WORDS] = 0;
	EXI_REGS[1 * EXI_CHAN_WORDS] = 0;
	EXI_REGS[2 * EXI_CHAN_WORDS] = 0;

	EXI_REGS[0 * EXI_CHAN_WORDS] = 0x2000;

	__OSSetInterruptHandler(9, (__OSInterruptHandler)EXIIntrruptHandler);
	__OSSetInterruptHandler(10, (__OSInterruptHandler)TCIntrruptHandler);
	__OSSetInterruptHandler(11, (__OSInterruptHandler)EXTIntrruptHandler);
	__OSSetInterruptHandler(12, (__OSInterruptHandler)EXIIntrruptHandler);
	__OSSetInterruptHandler(13, (__OSInterruptHandler)TCIntrruptHandler);
	__OSSetInterruptHandler(14, (__OSInterruptHandler)EXTIntrruptHandler);
	__OSSetInterruptHandler(15, (__OSInterruptHandler)EXIIntrruptHandler);
	__OSSetInterruptHandler(16, (__OSInterruptHandler)TCIntrruptHandler);

	EXIGetID(0, 2, &IDSerialPort1);

	if (__OSInIPL) {
		EXIProbeStartTime[1] = 0;
		EXIProbeStartTime[0] = 0;
		Ecb[1].idTime        = 0;
		Ecb[0].idTime        = 0;
		__EXIProbe(0);
		__EXIProbe(1);
	} else if (EXIGetID(0, 0, &id) && id == 0x07010000) {
		__OSEnableBarnacle(1, 0);
	} else if (EXIGetID(1, 0, &id) && id == 0x07010000) {
		__OSEnableBarnacle(0, 2);
	}

	OSRegisterVersion(__EXIVersion);
}

BOOL EXILock(s32 chan, u32 dev, EXICallback unlockedCallback)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;
	int i;

	enabled = OSDisableInterrupts();

	if (exi->state & EXI_STATE_LOCKED) {
		if (unlockedCallback) {
			for (i = 0; i < exi->items; i++) {
				if (exi->queue[i].dev == dev) {
					OSRestoreInterrupts(enabled);
					return FALSE;
				}
			}
			exi->queue[exi->items].callback = unlockedCallback;
			exi->queue[exi->items].dev      = dev;
			exi->items++;
		}
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->state |= EXI_STATE_LOCKED;
	exi->dev = dev;
	SetExiInterruptMask(chan, exi);

	OSRestoreInterrupts(enabled);
	return TRUE;
}

BOOL EXIUnlock(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	BOOL enabled;
	EXICallback unlockedCallback;

	enabled = OSDisableInterrupts();

	if (!(exi->state & EXI_STATE_LOCKED)) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	exi->state &= ~EXI_STATE_LOCKED;
	SetExiInterruptMask(chan, exi);

	if (exi->items > 0) {
		unlockedCallback = exi->queue[0].callback;
		if (--exi->items > 0) {
			memmove(&exi->queue[0], &exi->queue[1], (u32)exi->items * 8);
		}
		unlockedCallback(chan, NULL);
	}

	OSRestoreInterrupts(enabled);
	return TRUE;
}

// EXIGetState in the SDK: hands back the channel's state word.
u32 fn_801FBA04(s32 chan)
{
	EXIControl* exi = &Ecb[chan];

	return exi->state;
}

// Runs when a channel is handed back. Reading the ID is what notices that the
// device on the other end changed while the channel was held.
static void UnlockedHandler(s32 chan, void* context)
{
	u32 id;

	EXIGetID(chan, 0, &id);
}

s32 EXIGetID(s32 chan, u32 dev, u32* id)
{
	EXIControl* exi = &Ecb[chan];
	BOOL err;
	s32 startTime;
	BOOL enabled;

	if (chan == 0 && dev == 2 && IDSerialPort1 != 0) {
		*id = IDSerialPort1;
		return 1;
	}

	if (chan < 2 && dev == 0) {
		if (!__EXIProbe(chan)) {
			return 0;
		}

		if (exi->idTime == EXIProbeStartTime[chan]) {
			*id = exi->id;
			return exi->idTime;
		}

		if (!__EXIAttach(chan, NULL)) {
			return 0;
		}

		startTime = EXIProbeStartTime[chan];
	}

	enabled = OSDisableInterrupts();

	err = !EXILock(chan, dev, (chan < 2 && dev == 0) ? UnlockedHandler : NULL);
	if (!err) {
		if (!(err = !EXISelect(chan, dev, 0))) {
			u32 cmd = 0;

			err |= !EXIImm(chan, &cmd, 2, EXI_WRITE, NULL);
			err |= !EXISync(chan);
			err |= !EXIImm(chan, id, 4, EXI_READ, NULL);
			err |= !EXISync(chan);
			err |= !EXIDeselect(chan);
		}
		EXIUnlock(chan);
	}

	OSRestoreInterrupts(enabled);

	if (chan < 2 && dev == 0) {
		fn_801FAFB8(chan);

		enabled = OSDisableInterrupts();
		err |= (EXIProbeStartTime[chan] != startTime);
		if (!err) {
			exi->id     = *id;
			exi->idTime = startTime;
		}
		OSRestoreInterrupts(enabled);

		if (err) {
			return 0;
		}
		return exi->idTime;
	}

	return err ? 0 : 1;
}
