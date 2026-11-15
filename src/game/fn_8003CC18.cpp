#include "types.h"

// Finds the object a player stands on among its collision hits (fn_80020370 on the collision block
// +0x28, by index until it returns NULL): only while the player's collision flags (+0x30) have 0x10
// and 0x4 and its action flags (+0x6F6) lack 0x4. A hit counts when it is of kind 0 on a polygon
// (the object's polygon table +0x10, 0x30 bytes each) with flag 1, and the object is of type 4 or 5
// and either has flag 0x4 (+0x8; such a hit ends the search) or is the first one found without the
// hit flag 1 (+0x2). Returns the object and stores its polygon in *poly. HYPOTHESIS: the roles
// (moving platforms) are UNKNOWN.

struct Poly8003CC18 {
	u8 pad0[0x2];
	u8 flags; // 0x2
	u8 pad3[0x30 - 0x3];
};

struct Object8003CC18 {
	u16 type; // 0x0
	u8 pad2[0x8 - 0x2];
	u16 flags; // 0x8
	u8 padA[0x10 - 0xA];
	Poly8003CC18* polys; // 0x10
};

struct Hit8003CC18 {
	s8 kind;                // 0x0
	s8 poly;                // 0x1
	u16 flags;              // 0x2
	Object8003CC18* object; // 0x4
};

struct Player8003CC18 {
	u8 pad0[0x28];
	u8 colli[0x30 - 0x28]; // 0x28
	u16 colliFlags;        // 0x30
	u8 pad32[0x6F6 - 0x32];
	s16 actionFlags; // 0x6F6
};

extern "C" Hit8003CC18* fn_80020370(void* colli, s32 index);

static inline BOOL HasFlag10(u16 flags)
{
	if (flags & 0x10) {
		return TRUE;
	}
	return FALSE;
}

static inline BOOL HasFlag4(const Object8003CC18* object)
{
	if (object->flags & 0x4) {
		return TRUE;
	}
	return FALSE;
}

extern "C" Object8003CC18* fn_8003CC18(Player8003CC18* player, Poly8003CC18** poly)
{
	Object8003CC18* found = NULL;
	Hit8003CC18* hit;
	s32 i;

	u16 flags = player->colliFlags;
	if (!HasFlag10(flags) || !(flags & 0x4) || (player->actionFlags & 0x4)) {
		return NULL;
	}
	i = 0;
	while ((hit = fn_80020370(player->colli, i)) != NULL) {
		Poly8003CC18* p;
		Object8003CC18* object = hit->object;
		p                      = &object->polys[hit->poly];
		BOOL done              = FALSE;
		if (hit->kind == 0 && (p->flags & 1)) {
			BOOL priority = HasFlag4(object);
			s32 hitFlag   = hit->flags & 1;
			if (priority || (found == NULL && hitFlag == 0)) {
				switch (object->type) {
					case 4:
					case 5:
						found = object;
						if (poly != NULL) {
							*poly = p;
						}
						if (priority) {
							done = TRUE;
						}
						break;
				}
			}
		}
		i++;
		if (done) {
			break;
		}
	}
	return found;
}
