#include "types.h"

// The GameCube side of the debugger nub: bringing the target up, saving and
// restoring the register file across a break, and the nub's entry point.
// WORK IN PROGRESS: ten of thirteen functions are written and all ten match.
// What is left is TRKSaveExtended1Block, TRKRestoreExtended1Block and
// TRKLoadContext, all of them large.
//
// Built with GC/1.3.2 like the rest of TRK, not with the 1.2.5n the Dolphin SDK
// uses. See the TRK entry in configure.py.
//
// The translation unit runs from 0x801CF550 to 0x801CFAF4, where dolphin_trk.c
// starts. The ten functions in that range add up to exactly 0x5A4 bytes, which
// is the whole span, so nothing else belongs here and nothing is missing.
//
// This object is built with -sdata 0 -sdata2 0. Without them TRK_mainError is
// small enough for the small data area and its address comes out through r13,
// while the original builds it with an lis and addi pair. That alone was worth
// seventeen points on TRK_main. The last point came from claiming the .bss
// range in splits.txt and defining lbl_803F0050 here instead of reaching it as
// an external: until the range is claimed, dtk keeps calling a file local
// symbol TRK_mainError_803F0058 and nothing written in C can match that name.
//
// Functions are in the order the original emits them.

typedef int BOOL;

// The instruction and data breakpoint address registers, cleared on entry so a
// breakpoint left over from the last stop cannot fire inside the nub.
#define SPR_IABR 1010
#define SPR_DABR 1013

// Linker defined, see ldscript.lcf. Declared as an unsized array so the
// compiler cannot decide it is small enough to reach through r13.
extern char _db_stack_addr[];

extern void TRKSaveExtended1Block(void);
extern int  InitMetroTRKCommTable(u32 which);
extern void TRK_main(void);

// State the nub keeps about the target, 0xA4 bytes in .bss. Only the fields the
// written functions touch are named.
typedef struct TRKState {
	u8  unk00[0x8C]; // 0x00
	u32 unk8C;       // 0x8C, whatever fn_801CDCB8 reports
	u8  unk90[0x8];  // 0x90
	u32 unk98;       // 0x98, set to one on initialize
	u8  unk9C[0x8];  // 0x9C
} TRKState;          // 0xA4

extern TRKState gTRKState;

// The saved register file, 0x430 bytes. The word at 0x238 carries the flags
// fn_801CF650 tests.
extern u32 gTRKCPUState[];

// Base of the region the nub maps for itself, and the word after it. Owned by
// this file, so it is defined here rather than reached as an external.
static u32 lbl_803F0050[2];

extern u32  fn_801CDCB8(void);
extern void fn_801CFD74(void);

extern int  TRKInitializeNub(void);
extern void TRKNubWelcome(void);
extern int  TRKNubMainLoop(void);
extern int  TRKTerminateNub(void);

// Last result from TRK_main, kept so the host can read it back.
static int TRK_mainError;

// Four stubs that trap if anything reaches them. They are the unimplemented
// entries of the target interface: the nub declares them so the tables link,
// and traps rather than returning something wrong. Each one is a single
// unconditional twi followed by blr, which has no C form.

ASM void fn_801CF550(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

ASM void fn_801CF558(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

ASM void fn_801CF560(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

ASM void fn_801CF568(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

// Entered from whatever the game does to hand control to the debugger. It has
// to save the register file before touching anything, so it is assembly in the
// original source as well: there is no C for stmw, for moving the machine state
// register, or for writing the breakpoint address registers.
//
// The order matters. r3 is parked on the stack so it can be saved along with
// everything else, then the whole file goes out with one stmw. External
// interrupts are turned off in the copy of the MSR that is installed, while the
// original value is stashed in SRR1 for the return path.
ASM void InitMetroTRK(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	subi    r1, r1, 4
	stw     r3, 0(r1)
	lis     r3, gTRKCPUState@h
	ori     r3, r3, gTRKCPUState@l
	stmw    r0, 0(r3)
	lwz     r4, 0(r1)
	addi    r1, r1, 4
	stw     r1, 4(r3)
	stw     r4, 0xc(r3)
	mflr    r4
	stw     r4, 0x84(r3)
	stw     r4, 0x80(r3)
	mfcr    r4
	stw     r4, 0x88(r3)
	mfmsr   r4
	ori     r3, r4, 0x8000
	xori    r3, r3, 0x8000
	mtmsr   r3
	mtsrr1  r4
	bl      TRKSaveExtended1Block
	lis     r3, gTRKCPUState@h
	ori     r3, r3, gTRKCPUState@l
	lmw     r0, 0(r3)
	li      r0, 0
	mtspr   SPR_IABR, r0
	mtspr   SPR_DABR, r0
	lis     r1, _db_stack_addr@h
	ori     r1, r1, _db_stack_addr@l
	mr      r3, r5
	bl      InitMetroTRKCommTable
	cmpwi   r3, 1
	bne     _run
	lwz     r4, 0x84(r3)
	mtlr    r4
	lmw     r0, 0(r3)
	blr
_run:
	b       TRK_main
#endif // clang-format on
}

int TRKInitializeTarget(void)
{
	gTRKState.unk98 = 1;
	gTRKState.unk8C = fn_801CDCB8();

	lbl_803F0050[0] = 0xE0000000;

	return 0;
}

// Turns an address into the one the nub should actually touch. An address
// inside the nub's own region is left alone while the flags say it is live,
// because rewriting it would point the debugger at the wrong mapping. Anything
// else is forced through the cached mirror at 0x80000000.
static u32 fn_801CF650(u32 addr)
{
	if (addr >= lbl_803F0050[0] && addr < lbl_803F0050[0] + 0x4000
	    && (gTRKCPUState[0x238 / 4] & 3) != 0) {
		return addr;
	}

	return (addr & 0x3FFFFFFF) | 0x80000000;
}

void EnableMetroTRKInterrupts(void) { fn_801CFD74(); }

// TRKSaveExtended1Block and TRKRestoreExtended1Block belong here, still
// unwritten.

static int fn_801CFA20(void) { return 0x54; }

// The nub's whole life. Bring it up, greet the host, run until it is told to
// stop, then tear it down. Both results are stored where the host can read
// them, and the teardown result wins because it happens last.
void TRK_main(void)
{
	TRK_mainError = TRKInitializeNub();

	if (TRK_mainError == 0) {
		TRKNubWelcome();
		TRKNubMainLoop();
	}

	TRK_mainError = TRKTerminateNub();
}

// TRKLoadContext belongs here, still unwritten.
