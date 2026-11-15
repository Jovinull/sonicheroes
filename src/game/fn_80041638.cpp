#include "types.h"

// Walks the hits of an object's collision (fn_800211A8; each hit's +0x4 is the other object) for
// as long as the other object belongs to the same group: both ids (+0x78) are mapped as by
// fn_800419BC (ids 7..10 are their own group, the others go through the slot table lbl_80241C98
// and the group byte +0x25C of lbl_802AD0D0, 0 when unknown). Stops at the first hit of another
// group or when there is no more hit. HYPOTHESIS: the group is a team or character kind.
// NonMatching (one instruction shorter, registers): retail ends the body with beq to the loop
// test and b out (MWCC emits one bne out), and holds the two ids in r5/r6 (MWCC: r4/r5). Tried:
// continue/else/return exits, a bool helper, group locals, direct field arguments.

struct Object80041638 {
	u8 pad0[0x78];
	s32 id; // 0x78
};

struct Hit80041638 {
	u8 pad0[0x4];
	Object80041638* object; // 0x4
};

struct Slot80041638 {
	u8 pad0[0x25C];
	s8 group; // 0x25C
};

extern "C" {
extern s32 lbl_80241C98[6];
extern Slot80041638* lbl_802AD0D0[];
extern s32 lbl_80241CD8[];
Hit80041638* fn_800211A8(Object80041638* object);
}

static inline s32 FindIndex(s32 id)
{
	s32 i;

	for (i = 0; i < 6; i++) {
		if (id == lbl_80241C98[i]) {
			return i;
		}
	}
	return -1;
}

// The body of fn_800419BC.
static inline s32 Group(s32 id)
{
	s32 index;
	Slot80041638* slot;

	switch (id) {
		case 7:
		case 8:
		case 9:
		case 10:
			return id;
	}
	index = FindIndex(id);
	slot  = lbl_802AD0D0[index];
	if (index == -1 || slot == NULL) {
		return 0;
	}
	return lbl_80241CD8[slot->group];
}

static inline bool SameGroup(Object80041638* first, Object80041638* second)
{
	s32 a = first->id;
	s32 b = second->id;

	return Group(a) == Group(b);
}

static inline Object80041638* NextHit(Object80041638* object)
{
	Hit80041638* hit = fn_800211A8(object);

	return hit != NULL ? hit->object : NULL;
}

extern "C" void fn_80041638(Object80041638* object)
{
	Object80041638* other;

	while ((other = NextHit(object)) != NULL) {
		if (!SameGroup(object, other)) {
			break;
		}
	}
}
