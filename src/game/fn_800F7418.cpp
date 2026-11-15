#include "types.h"

// Whether an object touches something of another team: true when its collision block (+0x28)
// has a hit from fn_80020FD8, or when a hit object from fn_800211A8 or fn_800210C4 belongs to a
// team (fn_800419BC of the object's +0x78: kinds 7..10 are teams 0..3) other than the object's own
// (+0xF8; other kinds count as its own team). fn_80021824 restarts each scan. HYPOTHESIS: the three
// scans are the collision block's hit lists; the roles are UNKNOWN.
// NonMatching (one instruction moved per scan): retail sign-extends the team byte straight into
// the default team register (extsb r4, r0) and again for the comparison; MWCC extends once and
// copies it (mr r4, r0). Tried: a local, a u8 field with casts, the switch written in each loop,
// s8 locals and inline parameters.

struct Hit800F7418 {
	u8 pad0[0x78];
	void* owner; // 0x78
};

struct HitEntry800F7418 {
	u8 pad0[0x4];
	Hit800F7418* object; // 0x4
};

struct Object800F7418 {
	u8 pad0[0x28];
	u8 colli[0xF8 - 0x28]; // 0x28
	s8 team;               // 0xF8
};

extern "C" {
void fn_80021824(void* colli);
HitEntry800F7418* fn_80020FD8(void* colli);
HitEntry800F7418* fn_800211A8(void* colli);
HitEntry800F7418* fn_800210C4(void* colli);
s32 fn_800419BC(void* owner);
}

static inline Hit800F7418* HitObject(HitEntry800F7418* entry)
{
	if (entry != NULL) {
		return entry->object;
	}
	return NULL;
}

// The team of a hit object's owner: kinds 7..10 are teams 0..3, others the object's own.
static inline s32 OwnerTeam(s32 kind, s32 team)
{
	switch (kind) {
		case 7:
			team = 0;
			break;
		case 8:
			team = 1;
			break;
		case 9:
			team = 2;
			break;
		case 10:
			team = 3;
			break;
	}
	return team;
}

extern "C" s32 fn_800F7418(Object800F7418* object)
{
	Hit800F7418* hit;

	fn_80021824(object->colli);
	if (HitObject(fn_80020FD8(object->colli)) != NULL) {
		return 1;
	}
	fn_80021824(object->colli);
	while ((hit = HitObject(fn_800211A8(object->colli))) != NULL) {
		s32 kind = fn_800419BC(hit->owner);
		if (object->team != OwnerTeam(kind, object->team)) {
			return 1;
		}
	}
	fn_80021824(object->colli);
	while ((hit = HitObject(fn_800210C4(object->colli))) != NULL) {
		s32 kind = fn_800419BC(hit->owner);
		if (object->team != OwnerTeam(kind, object->team)) {
			return 1;
		}
	}
	return 0;
}
