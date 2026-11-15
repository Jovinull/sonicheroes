#include "game/rw_types.h"

// Picks the collision target a player can reach in a direction: walks the player's eight hit
// records (+0x3C, 8 bytes each, ended by a NULL object) and keeps the polygons of type 4, or of
// type 6 through the object's key-4 entry (fn_8001F9F8). For each one fn_8003B04C gives a point;
// the target qualifies when the yaw from the player's position (+0x708) to the point is within
// maxDiff of `angle` (DiffAngle), and the nearest one (DistanceP2P, below lbl_8042D1A0) wins.
// Returns its object and stores its polygon in *poly. HYPOTHESIS: the roles (grind rails, poles)
// are UNKNOWN. NonMatching (6 words): retail moves `angle` into r3 before converting the yaw (atan2
// result times lbl_8042D174) for the DiffAngle call; MWCC converts first. A float temporary (a
// local, or an inline returning the yaw) gives the retail order but renumbers every saved register
// (r23..r31 reversed); declaration permutations, an angle copy and operand order did not help.

struct Poly80041378 {
	u8 type; // 0x0
	u8 pad1[0x30 - 0x1];
};

struct Object80041378 {
	u8 pad0[0x10];
	Poly80041378* polys; // 0x10
};

struct Hit80041378 {
	s8 kind; // 0x0
	s8 poly; // 0x1
	u8 pad2[0x4 - 0x2];
	Object80041378* object; // 0x4
};

struct Player80041378 {
	u8 pad0[0x3C];
	Hit80041378 hits[8]; // 0x3C
	u8 pad7C[0x708 - 0x7C];
	RwV3d position; // 0x708
};

extern "C" {
extern const f32 lbl_8042D1A0;
extern const f32 lbl_8042D174; // radians to 16-bit angle units
double atan2(double y, double x);
Poly80041378* fn_8001F9F8(Object80041378* object, u8 key);
s32 fn_8003B04C(Object80041378* object, Poly80041378* poly, RwV3d* point);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);
f32 DistanceP2P(const RwV3d* first, const RwV3d* second);

extern "C" Object80041378* fn_80041378(
    Player80041378* player, s32 angle, s32 maxDiff, Poly80041378** poly)
{
	Hit80041378* hit      = player->hits;
	Hit80041378* end      = player->hits + 8;
	f32 best              = lbl_8042D1A0;
	Object80041378* found = NULL;

	for (; hit < end; hit++) {
		Object80041378* object = hit->object;
		if (object == NULL) {
			break;
		}
		Object80041378* target = NULL;
		Poly80041378* p        = &object->polys[hit->poly];
		switch (p->type) {
			case 6: {
				target          = object;
				Poly80041378* q = fn_8001F9F8(object, 4);
				if (q != NULL) {
					p = q;
				} else {
					target = NULL;
				}
				break;
			}
			case 4:
				target = object;
				break;
		}
		RwV3d point;
		if (target != NULL && fn_8003B04C(target, p, &point)) {
			if (maxDiff >= DiffAngle(angle,
			        lbl_8042D174
			            * (f32)atan2(point.x - player->position.x, point.z - player->position.z))) {
				f32 distance = DistanceP2P(&player->position, &point);
				if (distance < best) {
					best  = distance;
					found = target;
					if (poly != NULL) {
						*poly = p;
					}
				}
			}
		}
	}
	return found;
}
