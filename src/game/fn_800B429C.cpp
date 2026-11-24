// Per-frame update of a 43-entry manager (HYPOTHESIS; the owner is UNKNOWN, its neighbour
// fn_800B4684 works on the same entries): does nothing in mode 2, counts the byte 0x3 down to zero
// and runs fn_800B2330 on every entry in use (0x34 set). In mode 1 only entries whose 16-bit id
// (0x18) is in the six-id list lbl_802537E0 run; when the game state's byte 0x22 is 1, entries
// outside the eleven-id list lbl_802537EC have their value 0x12 clamped to 10 (out of 0..10) first.
// Both lists hold ids of category 14 (top nibble). The roles are UNKNOWN.
#include "types.h"

struct Entry800B429C {
	u8 pad0[0x12];
	s16 f12; // 0x12
	u8 pad14[0x18 - 0x14];
	u16 id; // 0x18
	u8 pad1A[0x34 - 0x1A];
	void* f34; // 0x34
};

struct Manager800B429C {
	s8 mode; // 0x0
	u8 pad1[0x3 - 0x1];
	s8 f3; // 0x3
	u8 pad4[0x8 - 0x4];
	Entry800B429C entries[43]; // 0x8
};

struct GameState800B429C {
	u8 pad0[0x22];
	s8 f22; // 0x22
};

extern "C" {
extern u16 lbl_802537E0[6];
extern u16 lbl_802537EC[11];
extern GameState800B429C* lbl_8042C180;
void fn_800B2330(Entry800B429C* entry);
}

static inline s32 IsInList1800B429C(u16 id)
{
	if ((u8)((id & 0xF000) >> 12) != 14) {
		return 0;
	}
	for (s8 i = 0; i < sizeof(lbl_802537E0) / sizeof(lbl_802537E0[0]); i++) {
		if (id == lbl_802537E0[i]) {
			return 1;
		}
	}
	return 0;
}

static inline s32 IsInList2800B429C(u16 id)
{
	if ((u8)((id & 0xF000) >> 12) != 14) {
		return 0;
	}
	for (s8 i = 0; i < sizeof(lbl_802537EC) / sizeof(lbl_802537EC[0]); i++) {
		if (id == lbl_802537EC[i]) {
			return 1;
		}
	}
	return 0;
}

extern "C" void fn_800B429C(Manager800B429C* m)
{
	s8 i;
	Entry800B429C* e;

	if (m->mode == 2) {
		return;
	}
	if (m->f3 > 0) {
		m->f3--;
	}
	e = m->entries;
	for (i = 0; i < 43; i++) {
		if (e->f34 == NULL) {
			e++;
			continue;
		}
		if (m->mode == 1 && IsInList1800B429C(e->id) == 0) {
			e++;
			continue;
		}
		if (lbl_8042C180->f22 == 1 && IsInList2800B429C(e->id) == 0) {
			if (e->f12 > 10 || e->f12 < 0) {
				e->f12 = 10;
			}
		}
		fn_800B2330(e);
		e++;
	}
}
