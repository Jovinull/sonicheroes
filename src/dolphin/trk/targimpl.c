#include "types.h"

// The GameCube side of the debugger nub: bringing the target up, saving and
// restoring the register file across a break, and the nub's entry point.
// WORK IN PROGRESS: five functions are written, five are still assembly.
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
// and traps rather than returning something wrong.
//
// fn_801CF550, fn_801CF558, fn_801CF560 and fn_801CF568 belong here, still
// unwritten.

// InitMetroTRK belongs here, still unwritten.

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
