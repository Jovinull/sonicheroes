#include "game/rw_types.h"

// Picks the target a player faces from its nearby-object list (lbl_8029EBC0 by the player number
// +0x760; 8-byte entries, an object and a key, ended by a NULL object): objects of type 2 or 3
// without a key-0x22 entry (fn_8001F9F8) and with a frame (+0x10), whose position (the frame's
// +0x8, plus the object's +0x60 unless the frame has flag 0x20) is at most lbl_8042D170 above the
// team leader (team +0x9B8: members +0x114, current +0x3B; its +0x70C) and, unless the player has
// flag 0x8000 (+0x780), within 0x5000 of the player's yaw (+0x700) as seen from its position
// (+0x708; atan2 of the Z and X offsets). The smallest key below lbl_8042D16C wins; returns its
// object. HYPOTHESIS: the roles are UNKNOWN (see fn_80040554).

struct Frame800406C0 {
	u8 pad0[0x4];
	u32 flags;      // 0x4
	RwV3d position; // 0x8
};

struct Object800406C0 {
	u16 type; // 0x0
	u8 pad2[0x10 - 0x2];
	Frame800406C0* frame; // 0x10
	u8 pad14[0x60 - 0x14];
	RwV3d position; // 0x60
};

struct Entry800406C0 {
	Object800406C0* object; // 0x0
	f32 key;                // 0x4
};

struct List800406C0 {
	Entry800406C0 entries[0x291];
};

struct Player800406C0;

struct Team800406C0 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player800406C0* members[3]; // 0x114
};

struct Player800406C0 {
	u8 pad0[0x700];
	s32 yaw; // 0x700
	u8 pad704[0x708 - 0x704];
	RwV3d position; // 0x708
	u8 pad714[0x760 - 0x714];
	s8 number; // 0x760
	u8 pad761[0x780 - 0x761];
	s32 flags; // 0x780
	u8 pad784[0x9B8 - 0x784];
	Team800406C0* team; // 0x9B8
};

extern "C" {
extern List800406C0 lbl_8029EBC0[8];
extern const f32 lbl_8042D16C;
extern const f32 lbl_8042D170;
extern const f32 lbl_8042D174; // radians to 16-bit angle units
double atan2(double y, double x);
void* fn_8001F9F8(Object800406C0* object, u8 key);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);

extern "C" Object800406C0* fn_800406C0(Player800406C0* player)
{
	Entry800406C0* entry  = lbl_8029EBC0[player->number].entries;
	Object800406C0* found = NULL;
	f32 best              = lbl_8042D16C;
	Team800406C0* team    = player->team;
	f32 top               = lbl_8042D170 + team->members[team->current]->position.y;

	for (; entry->object != NULL; entry++) {
		switch (entry->object->type) {
			case 2:
			case 3:
				break;
			default:
				continue;
		}
		if (fn_8001F9F8(entry->object, 0x22) != NULL) {
			continue;
		}
		Object800406C0* object = entry->object;
		Frame800406C0* frame   = object->frame;
		if (frame == NULL) {
			continue;
		}
		// Declared x, z, y: the retail float register numbering.
		f32 x;
		f32 z;
		f32 y;
		x = frame->position.x;
		y = frame->position.y;
		z = frame->position.z;
		if (!(frame->flags & 0x20)) {
			RwV3d base = object->position;
			x += base.x;
			y += base.y;
			z += base.z;
		}
		if (y > top) {
			continue;
		}
		x -= player->position.x;
		z -= player->position.z;
		s32 yaw = lbl_8042D174 * (f32)atan2(z, x);
		if (!(player->flags & 0x8000) && DiffAngle(player->yaw, yaw) > 0x5000) {
			continue;
		}
		if (entry->key < best) {
			best  = entry->key;
			found = entry->object;
		}
	}
	return found;
}
