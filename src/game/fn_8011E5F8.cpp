// Reports whether anything an object touches belongs to another team (HYPOTHESIS; names inferred):
// walks the object's collision lists (0x28: the current hit, then fn_800211A8 and fn_800210C4
// after each restart with fn_80021824). The current hit counts by itself; any other touched
// object counts when its kind (fn_800419BC of its 0x78) maps to a team other than the object's
// own (0xE8): kinds 7 to 10 are teams 0 to 3, any other kind keeps the object's team.
// Returns 1 when one counts, 0 otherwise. Built with the game-unit flags (-opt noschedule,
// nopeephole); fn_80119FEC and fn_80114588 are twins.
// NonMatching: retail sign-extends the team straight into the mapped-team register, while this
// source extends it into r0 and copies it (one move per loop; the rest shifts, 38 words). An
// inline mapping helper, a direct switch and team locals of either signedness keep the move.
#include "types.h"

struct Touched8011E5F8 {
	u8 pad0[0x78];
	void* kindSource; // 0x78
};

struct Hit8011E5F8 {
	u8 pad0[0x4];
	Touched8011E5F8* object; // 0x4
};

struct Owner8011E5F8 {
	u8 pad0[0x28];
	u8 colli[0xE8 - 0x28]; // 0x28: collision lists (C_COLLI, layout UNKNOWN)
	s8 team;               // 0xE8
};

extern "C" {
void fn_80021824(void* colli);
Hit8011E5F8* fn_80020FD8(void* colli);
Hit8011E5F8* fn_800211A8(void* colli);
Hit8011E5F8* fn_800210C4(void* colli);
s32 fn_800419BC(void* source);

static inline Touched8011E5F8* HitObject8011E5F8(Hit8011E5F8* hit)
{
	return hit != 0 ? hit->object : 0;
}

static inline s32 KindTeam8011E5F8(s32 kind, s32 team)
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

s32 fn_8011E5F8(Owner8011E5F8* owner)
{
	Touched8011E5F8* object;

	fn_80021824(owner->colli);
	if (HitObject8011E5F8(fn_80020FD8(owner->colli)) != 0) {
		return 1;
	}
	fn_80021824(owner->colli);
	while ((object = HitObject8011E5F8(fn_800211A8(owner->colli))) != 0) {
		s32 kind = fn_800419BC(object->kindSource);
		u8 team  = owner->team;
		if ((s8)team != KindTeam8011E5F8(kind, (s8)team)) {
			return 1;
		}
	}
	fn_80021824(owner->colli);
	while ((object = HitObject8011E5F8(fn_800210C4(owner->colli))) != 0) {
		s32 kind = fn_800419BC(object->kindSource);
		u8 team  = owner->team;
		if ((s8)team != KindTeam8011E5F8(kind, (s8)team)) {
			return 1;
		}
	}
	return 0;
}
}
