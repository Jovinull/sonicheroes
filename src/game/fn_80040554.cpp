#include "game/matrix.h"

// Picks the best target for a player within a range: walks the player's target list (lbl_802A9000
// by the player number +0x760; 8-byte entries, an object and a key, ended by a NULL object) and,
// for each object with a frame (+0x10), measures from the player's frame position (+0x38, +0x8) to
// the object's position (+0x60) plus the frame offset (+0x8). Of the targets within the range and
// below lbl_8042D168 on Y relative to the player, the one with the smallest key wins. Returns its
// entry, or NULL. HYPOTHESIS: homing-attack targeting; the roles are UNKNOWN.

struct Frame80040554 {
	u8 pad0[0x8];
	RwV3d position; // 0x8
};

struct Target80040554 {
	u8 pad0[0x10];
	Frame80040554* frame; // 0x10
	u8 pad14[0x60 - 0x14];
	RwV3d position; // 0x60
};

struct Entry80040554 {
	Target80040554* target; // 0x0
	f32 key;                // 0x4
};

struct List80040554 {
	Entry80040554 entries[0x101];
};

struct Player80040554 {
	u8 pad0[0x38];
	Frame80040554* frame; // 0x38
	u8 pad3C[0x760 - 0x3C];
	s8 number; // 0x760
};

extern "C" {
extern List80040554 lbl_802A9000[8];
extern const f32 lbl_8042D168;
f32 fn_801991B4(const RwV3d* v);
}

extern "C" Entry80040554* fn_80040554(Player80040554* player, f32 range)
{
	List80040554* list   = &lbl_802A9000[player->number];
	Entry80040554* entry = list->entries;
	Entry80040554* best;
	f32 bestKey;

	if (list->entries[0].target == NULL) {
		return NULL;
	}
	best = NULL;
	for (; entry->target != NULL; entry++) {
		Target80040554* target = entry->target;
		if (target->frame != NULL) {
			RwV3d offset;
			offset     = target->position;
			RwV3d base = target->frame->position;
			offset.x += base.x;
			offset.y += base.y;
			offset.z += base.z;
			offset.x -= player->frame->position.x;
			offset.y -= player->frame->position.y;
			offset.z -= player->frame->position.z;
			// "not beyond the range" (a single bgt), not "<=" (cror).
			if (!(fn_801991B4(&offset) > range) && offset.y < lbl_8042D168
			    && (best == NULL || entry->key < bestKey)) {
				bestKey = entry->key;
				best    = entry;
			}
		}
	}
	return best;
}
