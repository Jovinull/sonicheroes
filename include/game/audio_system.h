#ifndef GAME_AUDIO_SYSTEM_H
#define GAME_AUDIO_SYSTEM_H

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

struct PoolSlot {
	int active; // 0x00
	unsigned char pad4[0x1530 - 0x4];
};

struct PoolSystem {
	unsigned char pad0[0x505C];
	unsigned char busy[0x5478 - 0x505C]; // 0x505C: per-channel busy bytes
	PoolSlot slots[8];                   // 0x5478
	unsigned char padFDF8[0xFE04 - 0xFDF8];
	AXFX_REVERBSTD reverbStd; // 0xFE04: aux effect contexts selected by fn_80209CDC
	AXFX_REVERBHI reverbHi;   // 0xFF58
	AXFX_CHORUS chorus;       // 0x10138
	AXFX_DELAY delay;         // 0x101D4
	unsigned char pad10[0x13F6C - 0x101D4 - sizeof(AXFX_DELAY)];
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
