#include "game/rw_types.h"

// Counts the objects of a player's nearby-object list (lbl_8029EBC0 by the player number +0x760;
// 8-byte entries ended by a NULL object) that are near a point: objects of type 2 or 3 with a
// frame (+0x10) that is not of kind 0x1A, whose position (the frame's +0x8, plus the object's +0x60
// unless the frame has flag 0x20) is within lbl_8042E388 (squared, on XZ) of the point and, unless
// the player has flag 0x8000 (+0x780), within lbl_8042E384 of it on Y. HYPOTHESIS: the roles are
// UNKNOWN (see fn_80045148, which calls it with the player position).

struct Frame800EE0B4 {
	u8 kind; // 0x0
	u8 pad1[0x4 - 0x1];
	u32 flags;      // 0x4
	RwV3d position; // 0x8
};

struct Object800EE0B4 {
	u16 type; // 0x0
	u8 pad2[0x10 - 0x2];
	Frame800EE0B4* frame; // 0x10
	u8 pad14[0x60 - 0x14];
	RwV3d position; // 0x60
};

struct Entry800EE0B4 {
	Object800EE0B4* object; // 0x0
	u32 unknown4;           // 0x4
};

struct List800EE0B4 {
	Entry800EE0B4 entries[0x291];
};

struct Player800EE0B4 {
	u8 pad0[0x760];
	s8 number; // 0x760
	u8 pad761[0x780 - 0x761];
	u32 flags; // 0x780
};

extern "C" {
extern List800EE0B4 lbl_8029EBC0[8];
extern const f32 lbl_8042E384;
extern const f32 lbl_8042E388;
double __fabs(double x);
}

static inline BOOL IsNear(const Player800EE0B4* player, const Object800EE0B4* object,
    const Entry800EE0B4* entry, const RwV3d* point)
{
	s32 anyHeight = player->flags & 0x8000;
	switch (object->type) {
		case 2:
		case 3:
			break;
		default:
			return FALSE;
	}
	Frame800EE0B4* frame = object->frame;
	if (frame == NULL) {
		return FALSE;
	}
	if (frame->kind == 0x1A) {
		return FALSE;
	}
	RwV3d position = frame->position;
	if (!(frame->flags & 0x20)) {
		RwV3d base = entry->object->position;
		position.x += base.x;
		position.y += base.y;
		position.z += base.z;
	}
	if (anyHeight == 0 && (f32)__fabs(position.y - point->y) > lbl_8042E384) {
		return FALSE;
	}
	f32 dx = position.x - point->x;
	f32 dz = position.z - point->z;
	if (dx * dx + dz * dz > lbl_8042E388) {
		return FALSE;
	}
	return TRUE;
}

extern "C" s32 fn_800EE0B4(const Player800EE0B4* player, const RwV3d* point)
{
	List800EE0B4* list   = &lbl_8029EBC0[player->number];
	Entry800EE0B4* entry = list->entries;
	s32 count;

	if (list->entries[0].object != NULL) {
		count = 0;
		for (; entry->object != NULL; entry++) {
			if (IsNear(player, entry->object, entry, point)) {
				count++;
			}
		}
		return count;
	}
	return 0;
}
