#ifndef GAME_AUDIO_SYSTEM_H
#define GAME_AUDIO_SYSTEM_H

#include "dolphin/arq.h"
#include "dolphin/axfx.h"

// The audio system block at lbl_8042CF6C (fn_8020AD88 returns 0x0D000001 while that pointer is
// null): eight 0x1530-byte slots at 0x5478, the AXFX aux-effect contexts at 0xFE04 and 0x40 handles
// at 0x13F6C. Type and field names are inferred from the GameCube code; the subsystem's own names
// are not known.

struct PoolHandle {
	unsigned char active; // 0x00
	signed char channel;  // 0x01: index into PoolSystem::busy, negative when none
	unsigned char pad2[0x2];
	int param4;  // 0x04
	int param8;  // 0x08
	int paramC;  // 0x0C
	int param10; // 0x10
};

// Sixteen of these per slot, from slot offset 0xA4 (reset by fn_80209C48).
struct PoolChannel {
	int f00; // 0x00
	unsigned char pad04[0xC];
	int f10; // 0x10
	int f14; // 0x14
	int f18; // 0x18
	int f1C; // 0x1C
	int f20; // 0x20
	int f24; // 0x24
	int f28; // 0x28
	int f2C; // 0x2C: passed to fn_802073A0 by fn_80209318
	unsigned char pad30[0x8];
	unsigned int f38; // 0x38
	float f3C;        // 0x3C
	float f40;        // 0x40
	unsigned char pad44[0x4];
};

struct PoolSlot {
	int active;          // 0x00: bit 31 set while the slot runs (fn_80209A3C clears it)
	unsigned int flags4; // 0x04: bit 0 set while paused (fn_8020B730)
	// Two linear ramps advanced by fn_802092A8 and fn_8020917C: value moves from start to target
	// while remaining counts down from duration in steps of 5; remaining is -1 when idle.
	float rampAValue; // 0x08
	unsigned char padC[0x8];
	float rampATarget;    // 0x14
	float rampAStart;     // 0x18
	float rampADuration;  // 0x1C
	float rampARemaining; // 0x20
	float rampBValue;     // 0x24
	unsigned char pad28[0x4];
	float rampBTarget;    // 0x2C
	float rampBStart;     // 0x30
	float rampBDuration;  // 0x34
	float rampBRemaining; // 0x38
	unsigned char pad3C[0x40 - 0x3C];
	long long pauseTime; // 0x40: system time when paused
	unsigned char pad48[0xA0 - 0x48];
	unsigned int fA0;         // 0xA0: owned handle, released by fn_80209A3C
	PoolChannel channels[16]; // 0xA4
	unsigned char pad524[0x1530 - 0x524];
};

// 0x40 of these from system offset 0x54; fn_80208C38 counts the ones with a nonzero first word.
struct PoolEntry10C {
	int used; // 0x00
	unsigned char pad4[0x10C - 0x4];
};

// 0x40 of these from system offset 0x4354; fn_80206F04 counts the ones with a nonzero first byte.
struct PoolEntry14 {
	unsigned char used; // 0x00
	unsigned char pad1[0x14 - 0x1];
};

// 0x20-byte heap block header: "MF" for a free block, "MB" for a used block and the end marker
// (fn_80205DF4, fn_80205CBC). The memory handed out follows the header.
struct PoolHeapBlock {
	unsigned short tag;  // 0x00
	unsigned short f2;   // 0x02
	PoolHeapBlock* next; // 0x04
	unsigned char pad8[0x18];
};

struct PoolSystem {
	int f00;  // 0x00: nonzero once the system runs
	int pad4; // 0x04
	int lock; // 0x08: update nesting count, changed with interrupts disabled
	int f0C;  // 0x0C: result of fn_80208C38
	int f10;  // 0x10: result of fn_80206F04
	int pad14;
	long long time;     // 0x18: OSGetTime() of the current update
	long long prevTime; // 0x20
	unsigned char pad28[0x44 - 0x28];
	int f44; // 0x44: 1 keeps a paused slot's handle (fn_802066AC) instead of releasing it
	unsigned char pad48[0x54 - 0x48];
	PoolEntry10C entries10C[0x40];  // 0x54
	PoolEntry14 entries14[0x40];    // 0x4354
	unsigned char* heap;            // 0x4854: 32-byte aligned heap start (fn_80205DF4)
	unsigned int heapSize;          // 0x4858
	ARQRequest requests[0x40];      // 0x485C: ARAM transfers posted by fn_80205848
	unsigned char busy[0x40];       // 0x505C: nonzero while the request is in flight
	unsigned int arqOwner;          // 0x509C
	unsigned int requestArgA[0x40]; // 0x50A0
	unsigned int requestArgB[0x40]; // 0x51A0
	unsigned char pad52A0[0x8];
	int arenaFree; // 0x52A8: bytes left for fn_80206104
	int arenaNext; // 0x52AC: offset of the next region
	unsigned char pad52B0[0x52F8 - 0x52B0];
	struct {
		int offset;
		int size;
	} regions[0x10]; // 0x52F8: reserved by fn_80206104
	struct {
		unsigned char* data; // 0x5378: loaded bank image, or null
		unsigned int pad4;
	} banks[0x20];
	PoolSlot slots[8]; // 0x5478
	unsigned char padFDF8[0xFE04 - 0xFDF8];
	AXFX_REVERBSTD reverbStd; // 0xFE04: aux effect contexts selected by fn_80209CDC
	AXFX_REVERBHI reverbHi;   // 0xFF58
	AXFX_CHORUS chorus;       // 0x10138
	AXFX_DELAY delay;         // 0x101D4
	unsigned char pad10[0x13A3B - 0x101D4 - sizeof(AXFX_DELAY)];
	unsigned char skipped; // 0x13A3B: updates skipped because one was already running
	unsigned char pad13A3C[0x13F6C - 0x13A3C];
	PoolHandle handles[0x40]; // 0x13F6C
	unsigned char f1446C;     // 0x1446C: passed to the bank loaders
};

extern "C" PoolSystem* lbl_8042CF6C;

// 0 for an active record of the pool, 0x07000103 for null, 0x07000102 otherwise.
static inline int CheckPoolHandle(PoolSystem* sys, PoolHandle* h)
{
	int i;
	if (h == 0) {
		return 0x07000103;
	}
	for (i = 0; i < 0x40; i++) {
		if (h == &sys->handles[i]) {
			if (h->active == 0) {
				break;
			}
			return 0;
		}
	}
	return 0x07000102;
}

// 0 for an active slot of the pool, 0x07000103 for null, 0x07000102 otherwise.
static inline int CheckPoolSlot(PoolSystem* sys, PoolSlot* s)
{
	int i;
	if (s == 0) {
		return 0x07000103;
	}
	for (i = 0; i < 8; i++) {
		if (s == &sys->slots[i]) {
			if (s->active == 0) {
				break;
			}
			return 0;
		}
	}
	return 0x07000102;
}

#endif
