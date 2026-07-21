#include "types.h"

// The battery backed settings block. WORK IN PROGRESS: three functions are
// written, the rest are still assembly in the build.
//
// The translation unit runs from __OSInitSram at 0x801D5594 to 0x801D6264.
// Before it is game code, after it is __OSInitSystemCall, which belongs
// elsewhere. Functions are in the order the original emits them.

typedef int BOOL;

// The control block, 0x54 bytes in .bss at 0x803F2360. Only the field the
// written functions touch is named; the rest is padding until something proves
// what it holds.
typedef struct SramControl {
	u8   unk00[0x4C]; // 0x00
	BOOL sync;        // 0x4C
	u8   unk50[0x4];  // 0x50
} SramControl;        // 0x54

static SramControl Scb;

// The core of the unlock, written below. Both wrappers reach it with a
// different offset: the plain one commits from the start of the block, the Ex
// one from 0x14 in, which is where the part the games are allowed to touch
// begins.
static void fn_801D5788(BOOL commit, u32 offset);

// __OSInitSram, __OSLockSram and __OSLockSramEx belong here, still unwritten.

// fn_801D5788 belongs here, still unwritten.

void __OSUnlockSram(BOOL commit)
{
	fn_801D5788(commit, 0);
}

void __OSUnlockSramEx(BOOL commit)
{
	fn_801D5788(commit, 0x14);
}

// Reports whether the block has finished being written back.
BOOL __OSSyncSram(void)
{
	return Scb.sync;
}

// The remaining accessors belong here, still unwritten.
