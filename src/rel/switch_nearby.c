#include "types.h"

// Finds the nearest object of kind 0x24 in the switch's group. If one is close
// enough, its target is marked with the engine's sentinel and receives the
// switch placement's position.
//
// The claim is .text 0x42B8 to 0x4398. The routine is identical in the thirteen
// stage modules that share the common object engine.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Target {
	u32 sentinel;
	Vec3 position;
} Target;

typedef struct SetEntry {
	Vec3 position;         // 0x00
	u8 unkC[0x1C];         // 0x0C
	u16 kind;              // 0x28
	u8 group;              // 0x2A
	u8 unk2B[0x5];         // 0x2B
	Target* target;        // 0x30
	u8 unk34[0x4];         // 0x34
	struct SetEntry* next; // 0x38
} SetEntry;

typedef struct Manager {
	u8 unk0[0x30];
	SetEntry* groups[1];
} Manager;

typedef struct Switch {
	u8 unk0[0x28];
	SetEntry* entry;
} Switch;

extern "C" Manager* lbl_8042C298;
extern "C" const f32 switchNearbyRange;

extern "C" f32 fn_800D71DC(SetEntry* from, SetEntry* to);

extern "C" void switchActivateNearby(Switch* object)
{
	if (object->entry->target != NULL) {
		SetEntry* candidate = lbl_8042C298->groups[object->entry->group];
		f32 range           = switchNearbyRange;

		while (candidate != NULL) {
			if (candidate->kind == 0x24 && fn_800D71DC(object->entry, candidate) < range) {
				object->entry->target->sentinel = 0x12345678;
				Target* target;
				SetEntry* entry;
				entry              = object->entry;
				target             = entry->target;
				target->position.x = entry->position.x;
				target->position.y = entry->position.y;
				target->position.z = entry->position.z;
				break;
			}
			candidate = candidate->next;
		}
	}
}
