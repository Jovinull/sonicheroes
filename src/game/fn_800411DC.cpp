// Promotes an object's pending target (+0x680, with its data +0x684) to the current one
// (+0x678/+0x67C) once the object has no current target and touches the pending one (the check of
// fn_800414E4, inlined); clears the pending pair and returns 1, else 0. HYPOTHESIS: a player
// "grab" target confirmed on contact; the roles are UNKNOWN.
#include "types.h"

struct Hit800411DC {
	u8 pad0[4];
	void* other; // 0x4
};

struct Obj800411DC {
	u8 pad0[0x28];
	u8 colli[0x88]; // 0x28 (C_COLLI)
	u8 padB0[0x678 - 0xB0];
	void* current;   // 0x678
	s32 currentData; // 0x67C
	void* pending;   // 0x680
	s32 pendingData; // 0x684
};

extern "C" {
void fn_80021824(void* colli);
Hit800411DC* fn_80020BD8(void* colli, u8 kind);
}

// The object hit, or null when there is no hit.
static inline void* HitObject(Hit800411DC* hit)
{
	return hit != NULL ? hit->other : NULL;
}

// Body of fn_800414E4.
static inline s32 IsTouching(Obj800411DC* o, void* target)
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

extern "C" s32 fn_800411DC(Obj800411DC* o)
{
	if (o->current == NULL && o->pending != NULL && IsTouching(o, o->pending)) {
		o->current     = o->pending;
		o->currentData = o->pendingData;
		o->pending     = NULL;
		o->pendingData = 0;
		return 1;
	}
	return 0;
}
