#include "game/rw_types.h"

// Gives the horizontal direction from a player's rail point to the player: the rail (object and
// polygon) is the pair at +0x678/+0x67C or, failing that, +0x680/+0x684; it must still be among
// the player's collision hits of kind 4 or 6 (fn_80020BD8 on the collision block +0x28, restarted
// by fn_80021824). fn_8003B04C gives the point on it; the offset from that point to the player's
// frame position (+0x38, +0x8) with Y set to lbl_8042D178 is normalized into *direction
// (fn_801990E0) unless it is shorter than lbl_8042D19C (squared). Returns whether it worked.
// HYPOTHESIS: grind rails; the roles are UNKNOWN (see fn_80041378).

struct Poly8004102C;

struct Object8004102C;

struct Hit8004102C {
	u8 pad0[0x4];
	Object8004102C* object; // 0x4
};

struct Frame8004102C {
	u8 pad0[0x8];
	RwV3d position; // 0x8
};

struct Player8004102C {
	u8 pad0[0x28];
	u8 colli[0x38 - 0x28]; // 0x28
	Frame8004102C* frame;  // 0x38
	u8 pad3C[0x678 - 0x3C];
	Object8004102C* object;  // 0x678
	Poly8004102C* poly;      // 0x67C
	Object8004102C* object2; // 0x680
	Poly8004102C* poly2;     // 0x684
};

extern "C" {
extern const f32 lbl_8042D178;
extern const f32 lbl_8042D19C;
void fn_80021824(void* colli);
Hit8004102C* fn_80020BD8(void* colli, s32 kind);
s32 fn_8003B04C(Object8004102C* object, Poly8004102C* poly, RwV3d* point);
f32 fn_801990E0(RwV3d* out, const RwV3d* in);
}

extern "C" s32 fn_8004102C(Player8004102C* player, RwV3d* direction)
{
	Poly8004102C* poly;
	Object8004102C* object;
	Hit8004102C* hit;
	RwV3d point;

	if (player->object != NULL && player->poly != NULL) {
		poly   = player->poly;
		object = player->object;
	} else if (player->object2 != NULL && player->poly2 != NULL) {
		poly   = player->poly2;
		object = player->object2;
	} else {
		return 0;
	}
	fn_80021824(player->colli);
	while ((hit = fn_80020BD8(player->colli, 4)) != NULL) {
		if (hit->object == object) {
			break;
		}
	}
	if (hit == NULL) {
		fn_80021824(player->colli);
		while ((hit = fn_80020BD8(player->colli, 6)) != NULL) {
			if (hit->object == object) {
				break;
			}
		}
	}
	if (hit == NULL) {
		return 0;
	}
	if (fn_8003B04C(object, poly, &point) == 0) {
		return 0;
	}
	direction->x = player->frame->position.x - point.x;
	direction->y = player->frame->position.y - point.y;
	direction->z = player->frame->position.z - point.z;
	direction->y = lbl_8042D178;
	if (direction->z * direction->z + (direction->x * direction->x + direction->y * direction->y)
	    <= lbl_8042D19C) {
		return 0;
	}
	fn_801990E0(direction, direction);
	return 1;
}
