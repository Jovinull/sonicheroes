#include "types.h"

// The external interface bus driver. WORK IN PROGRESS: six functions are
// written, the other sixteen are still assembly in the build.
//
// The translation unit runs from EXIImm at 0x801FA50C to the end of EXIGetID at
// 0x801FBDF4. Before it is SI and game code, after it is __OSEnableBarnacle,
// which belongs to OS. The functions with no name yet are static helpers of
// this file: nothing outside the range calls them.
//
// Functions are in the order the original emits them, which is source order for
// this compiler. The gaps below mark what is not written yet.
//
// What is written and where it stands:
//   EXIClearInterrupts 76.1%  the original builds a pointer to the channel's
//                             status register and loads through it, ours
//                             indexes and the compiler picks a different
//                             addressing form. Four spellings of the register
//                             block and four shapes of the access expression
//                             were measured and every one that compiles lands
//                             on the same number, so it is not the spelling.
//   UnlockedHandler    74.0%  one instruction, the zero argument is scheduled
//                             before the buffer address instead of after.
//   fn_801FBA04        61.7%  the original computes the channel offset first
//                             and materializes the control block after; ours
//                             does it the other way round. Five ways of
//                             forming the element address were measured and
//                             four of them tie, so the order does not come
//                             from the expression.
//   fn_801FAD78        65.9%  same ordering problem, plus the probe test comes
//                             out inverted.
//   fn_801FAB88        65.9%  same ordering problem, and one callee saved
//                             register fewer than the original keeps.
//   EXTIntrruptHandler 41.1%  the channel divide is scheduled before the
//                             prologue saves rather than after, and the frame
//                             holds one register fewer.
//
// A note on reading these numbers: the control block is a file local symbol, so
// dtk names it Ecb in our object and Ecb_8040EA90 in the extracted one. Every
// relocation that touches it counts as a mismatch even where the instruction is
// identical, which makes all four of the above look worse than they are.

// The register block gives each of the three channels five words: status at 0,
// then the DMA address, the length, the control word and the immediate data.
// Indexing a base pointer rather than naming absolute addresses is what makes
// the compiler compute one channel offset and reuse it.
#define EXI_REGS ((volatile u32*)0xCC006800)
#define EXI_CHAN_WORDS 5

// Status register bits. The mask is everything that has to survive a write,
// the three flags below are write-one-to-clear interrupt causes.
#define EXI_CSR_KEEP 0x7F5
#define EXI_CSR_EXI  0x0002
#define EXI_CSR_TC   0x0008
#define EXI_CSR_EXT  0x0800

#define NULL 0
#define FALSE 0
#define TRUE  1

typedef int BOOL;

typedef void (*EXICallback)(s32 chan, void* context);

// One control block per channel, 0x40 bytes each, in .bss at 0x8040EA90. Only
// the fields the written functions touch are named; the rest is padding until
// something proves what it holds.
//
// The field at 0x0C is state, not an identifier: EXTIntrruptHandler reads it,
// clears one bit and writes it back.
typedef struct EXIControl {
	EXICallback exiCallback; // 0x00
	u8          unk04[0x4];  // 0x04
	EXICallback extCallback; // 0x08
	u32         state;       // 0x0C
	u8          unk10[0x10]; // 0x10
	u32         id;          // 0x20
	u8          unk24[0x1C]; // 0x24
} EXIControl;                // 0x40

// Cleared by the external interrupt once it has been taken.
#define EXI_STATE_ATTACHED 0x8

// The context saved across a callback. Its size is why the external handler
// takes a 0x2E8 byte frame.
typedef struct OSContext {
	u8 pad[0x2C8];
} OSContext;

extern EXIControl Ecb[3];

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32  __OSMaskInterrupts(u32 mask);
extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);

extern void SetExiInterruptMask(s32 chan, EXIControl* exi);
extern BOOL __EXIProbe(s32 chan);
extern s32  EXIGetID(s32 chan, u32 dev, u32* id);

// EXIImm, fn_801FA768, EXIDma and EXISync belong here, still unwritten.

// Acknowledges whichever of the three interrupt causes the caller names and
// hands back the status word as it was before the write. The causes are write
// one to clear, so the ones not named have to be masked out rather than left
// alone, or acknowledging one would acknowledge all three.
static u32 EXIClearInterrupts(s32 chan, BOOL exi, BOOL tc, BOOL ext)
{
	u32 cpr;
	u32 v;

	cpr = EXI_REGS[chan * EXI_CHAN_WORDS];

	v = cpr & EXI_CSR_KEEP;
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

// Swaps in a new callback for the channel's own interrupt and hands back the
// one that was there. Channel 2 has no mask of its own, so the mask for
// channel 0 is what gets recomputed on its behalf.
static EXICallback fn_801FAB88(s32 chan, EXICallback exiCallback)
{
	EXIControl* exi = &Ecb[chan];
	BOOL        enabled;
	EXICallback prev;

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

// __EXIProbe belongs here, still unwritten.

// Answers whether something is attached and identified. A probe on its own is
// not enough: a channel that has never reported an identifier gets asked for
// one, and only a successful answer counts as attached.
static BOOL fn_801FAD78(s32 chan)
{
	EXIControl* exi = &Ecb[chan];
	u32         id;

	if (!__EXIProbe(chan)) {
		return FALSE;
	}

	if (exi->id != 0) {
		return TRUE;
	}

	if (EXIGetID(chan, 0, &id) != 0) {
		return TRUE;
	}

	return FALSE;
}

// fn_801FADF8, fn_801FAEAC, fn_801FAFB8, EXISelect, EXIDeselect,
// EXIIntrruptHandler and TCIntrruptHandler belong here, still unwritten.

// The external interrupt says a device was inserted or removed. The interrupt
// numbers for the three channels are three apart starting at 0x0B, which is
// where the divide comes from. The callback runs on a context of its own so
// that whatever it does cannot disturb the one that was interrupted.
static void EXTIntrruptHandler(s16 interrupt, OSContext* context)
{
	s32         chan;
	EXIControl* exi;
	EXICallback callback;
	OSContext   exiContext;

	chan = (interrupt - 0xB) / 3;
	__OSMaskInterrupts(0x500000 >> (chan * 3));

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

// EXIInit, EXILock and EXIUnlock belong here, still unwritten.

// Hands back the channel's state word.
static u32 fn_801FBA04(s32 chan)
{
	EXIControl* exi;

	exi = &Ecb[chan];
	return exi->state;
}

// Runs when a channel is handed back. Reading the ID is what notices that the
// device on the other end changed while the channel was held.
static void UnlockedHandler(s32 chan, void* context)
{
	u32 id;

	EXIGetID(chan, 0, &id);
}

// EXIGetID belongs here, still unwritten.
