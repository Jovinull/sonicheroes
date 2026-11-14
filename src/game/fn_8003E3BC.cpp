// Sets a player's position (HYPOTHESIS: a PlayerMaster member; the first argument is the unused
// PlayerMaster): when the player slot lbl_802AD090[index] is in use, writes the position to the
// player object at 0x18 and to the player's current entry of the position history ring
// lbl_8042C1B0 (256 entries per player, current entry lbl_8042C1A8[index]).
#include "types.h"

struct Vec8003E3BC {
	f32 x;
	f32 y;
	f32 z;
};

// Player object fields used here.
struct Player8003E3BC {
	u8 pad0[0x18];
	Vec8003E3BC position; // 0x18
};

extern "C" {
extern Player8003E3BC* lbl_802AD090[8];
extern u8 lbl_8042C1A8[8];
extern Vec8003E3BC* lbl_8042C1B0;

void fn_8003E3BC(void* master, s32 index, f32 x, f32 y, f32 z)
{
	// Current ring entry, computed like GetPlayerPositionHistory__12PlayerMasterFiUc with no
	// offset back (the retail code keeps the byte truncation of that subtraction).
	u8 slot = lbl_8042C1A8[index] - 0;

	if (lbl_802AD090[index]) {
		lbl_802AD090[index]->position.x     = x;
		lbl_802AD090[index]->position.y     = y;
		lbl_802AD090[index]->position.z     = z;
		lbl_8042C1B0[slot + (index << 8)].x = x;
		lbl_8042C1B0[slot + (index << 8)].y = y;
		lbl_8042C1B0[slot + (index << 8)].z = z;
	}
}
}
