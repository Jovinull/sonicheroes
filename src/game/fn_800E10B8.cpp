// Sets the velocity (x, y, z) of player `index`: stores it in the player's motion record
// (lbl_802AD0B0), converts a copy with fn_8003EB18 on the state record (lbl_802AD090), snaps its
// x and z components within 0.001 of zero to 0 and stores the result at +0x60 of the path record
// (lbl_802AD0D0). HYPOTHESIS: world-to-local velocity; the roles are UNKNOWN.
#include "types.h"

struct Vec800E10B8 {
	f32 x;
	f32 y;
	f32 z;
};

struct Ctrl800E10B8 {
	u8 pad0[0x60];
	Vec800E10B8 velocity; // 0x60
};

extern "C" {
extern void* lbl_802AD090[8];
extern Vec800E10B8* lbl_802AD0B0[8];
extern Ctrl800E10B8* lbl_802AD0D0[8];
extern f32 lbl_8042E214; // 0.001f
extern f32 lbl_8042E218; // -0.001f
extern f32 lbl_8042E1F0; // 0.0f
void fn_8003EB18(void* state, Vec800E10B8* v);

// The retail code reloads the 0.001 constant for the second component (no common subexpression
// elimination in this function).
#pragma opt_common_subs off
void fn_800E10B8(s32 index, f32 x, f32 y, f32 z)
{
	void* state         = lbl_802AD090[index];
	Vec800E10B8* motion = lbl_802AD0B0[index];
	Ctrl800E10B8* ctrl  = lbl_802AD0D0[index];
	Vec800E10B8 v;

	motion->x = x;
	motion->y = y;
	motion->z = z;
	v.x       = x;
	v.y       = y;
	v.z       = z;
	fn_8003EB18(state, &v);
	if (v.x <= lbl_8042E214 && v.x >= lbl_8042E218) {
		v.x = lbl_8042E1F0;
	}
	if (v.z <= lbl_8042E214 && v.z >= lbl_8042E218) {
		v.z = lbl_8042E1F0;
	}
	ctrl->velocity = v;
}
#pragma opt_common_subs reset
}
