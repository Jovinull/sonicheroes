// Whether an object's collision (+0x28) has a hit against `target` on another object's shape of
// kind 4 or kind 6 (the cached hit iterator fn_80020BD8, restarted with fn_80021824); 0 for a null
// target. HYPOTHESIS: "is touching" between an object and a player; the kinds' meanings are
// UNKNOWN.
#include "types.h"

struct Hit800414E4 {
	u8 pad0[4];
	void* other; // 0x4
};

struct Obj800414E4 {
	u8 pad0[0x28];
	u8 colli[0x88]; // 0x28 (C_COLLI)
};

extern "C" {
void fn_80021824(void* colli);
Hit800414E4* fn_80020BD8(void* colli, u8 kind);
}

// The object hit, or null when there is no hit.
static inline void* HitObject(Hit800414E4* hit)
{
	return hit != NULL ? hit->other : NULL;
}

extern "C" s32 fn_800414E4(Obj800414E4* o, void* target)
{
	void* other;

	if (target != NULL) {
		fn_80021824(o->colli);
		while ((other = HitObject(fn_80020BD8(o->colli, 4))) != NULL) {
			if (other == target) {
				return 1;
			}
		}
		while ((other = HitObject(fn_80020BD8(o->colli, 6))) != NULL) {
			if (other == target) {
				return 1;
			}
		}
	}
	return 0;
}
