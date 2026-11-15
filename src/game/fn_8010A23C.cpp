// Returns whether the object's collision (0x28) touches anything that blocks it (HYPOTHESIS;
// names inferred): any first hit (fn_80020FD8), a hit of either shape pass (fn_800211A8,
// fn_800210C4) whose owner's type maps to a team other than the object's (types 7-10 are the
// four teams; other types count as the same team), or a hit of kind 11.
// NonMatching: retail sign-extends the team byte again for the comparison; this draft reuses the
// extended value and adds one register copy in each team check.
#include "types.h"

struct Colli8010A23C {
	u8 pad0[0x78];
	void* owner; // 0x78
};

struct HitInfo8010A23C {
	s8 my_num;
	s8 hit_num;
	u16 flag;
	Colli8010A23C* hit_ccl; // 0x4
};

struct Object8010A23C {
	u8 pad0[0x28];
	u8 colli[0xF0 - 0x28]; // 0x28
	s8 team;               // 0xF0
};

extern "C" {
void fn_80021824(void* colli);
HitInfo8010A23C* fn_80020FD8(void* colli);
HitInfo8010A23C* fn_800211A8(void* colli);
HitInfo8010A23C* fn_800210C4(void* colli);
HitInfo8010A23C* fn_80020BD8(void* colli, s32 kind);
s32 fn_800419BC(void* object);
}

static inline Colli8010A23C* hitColli(HitInfo8010A23C* hit)
{
	return hit != 0 ? hit->hit_ccl : 0;
}

// Team of an object type (7-10 are the four teams); other types keep the given team.
static inline s32 teamOfType(s32 type, s32 team)
{
	switch (type) {
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

extern "C" s32 fn_8010A23C(Object8010A23C* self)
{
	Colli8010A23C* other;

	fn_80021824(self->colli);
	if (hitColli(fn_80020FD8(self->colli)) != 0) {
		return 1;
	}
	fn_80021824(self->colli);
	while ((other = hitColli(fn_800211A8(self->colli))) != 0) {
		s32 type = fn_800419BC(other->owner);
		if (self->team != teamOfType(type, self->team)) {
			return 1;
		}
	}
	fn_80021824(self->colli);
	while ((other = hitColli(fn_800210C4(self->colli))) != 0) {
		s32 type = fn_800419BC(other->owner);
		if (self->team != teamOfType(type, self->team)) {
			return 1;
		}
	}
	fn_80021824(self->colli);
	while (hitColli(fn_80020BD8(self->colli, 11)) != 0) {
		return 1;
	}
	return 0;
}
