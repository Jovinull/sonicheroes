// Enemy check (HYPOTHESIS: "is landed or blocked"): restarts the hit search (fn_80021824 on the
// cache lbl_8042C1A4) and, while the enemy's collision (+0x28) has a hit against another object's
// shape of kind 0xD (the iterator fn_80020BD8), returns 1 when its collision flag 0x20 (+0x30) is
// set; otherwise returns whether the value at +0x1A4 is at most 0. Roles are UNKNOWN.
#include "types.h"

struct Hit800A3ED4 {
	u8 pad0[4];
	void* other; // 0x4
};

struct Enemy800A3ED4 {
	u8 pad0[0x28];
	u8 colli[8];    // 0x28 (C_COLLI)
	u16 colliFlags; // 0x30 (C_COLLI +0x8)
	u8 pad32[0x1A4 - 0x32];
	f32 unknown1A4; // 0x1A4
};

extern "C" {
extern u8 lbl_8042C1A4;  // small-data search cache (only its address is used)
extern f32 lbl_8042DA74; // 0.0f
void fn_80021824(void* cache);
Hit800A3ED4* fn_80020BD8(void* colli, u8 kind);
}

// The object hit, or null when there is no hit.
static inline void* HitObject(Hit800A3ED4* hit)
{
	return hit != NULL ? hit->other : NULL;
}

extern "C" s32 fn_800A3ED4(Enemy800A3ED4* e)
{
	fn_80021824(&lbl_8042C1A4);
	while (HitObject(fn_80020BD8(e->colli, 0xD)) != NULL) {
		if (e->colliFlags & 0x20) {
			return 1;
		}
	}
	return e->unknown1A4 <= lbl_8042DA74;
}
