#include "types.h"

// The external interface bus driver. WORK IN PROGRESS: three functions are
// written, the other nineteen are still assembly in the build.
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
//   fn_801FBA04        59.2%  the original computes the channel offset first
//                             and materializes the control block after; ours
//                             does it the other way round.

typedef int BOOL;

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

// One control block per channel, 0x40 bytes each, in .bss at 0x8040EA90.
typedef struct EXIControl {
	u8 pad[0xC]; // 0x00
	u32 id;      // 0x0C
	u8 rest[48]; // 0x10
} EXIControl;

extern EXIControl Ecb[3];

extern s32 EXIGetID(s32 chan, u32 dev, u32* id);

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

// fn_801FAB88, __EXIProbe, fn_801FAD78, fn_801FADF8, fn_801FAEAC, fn_801FAFB8,
// EXISelect, EXIDeselect, EXIIntrruptHandler, TCIntrruptHandler,
// EXTIntrruptHandler, EXIInit, EXILock and EXIUnlock belong here, still
// unwritten.

static u32 fn_801FBA04(s32 chan)
{
	return Ecb[chan].id;
}

// Runs when a channel is handed back. Reading the ID is what notices that the
// device on the other end changed while the channel was held.
static void UnlockedHandler(s32 chan, void* context)
{
	u32 id;

	EXIGetID(chan, 0, &id);
}

// EXIGetID belongs here, still unwritten.
