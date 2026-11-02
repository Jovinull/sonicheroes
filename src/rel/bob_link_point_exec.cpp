#include "types.h"

// The exec step of the special stages' second sled link class
// (bobLinkPointExec here; the class has no PS2 name), in stage01D and
// stage07D. As bobLinkAttachExec (asks to be killed outside the play mode,
// waits while paused unless flag 8 lets it run), but in mode 1 the target
// follows the object's point every frame, and only a running timer that
// reaches zero ends the link: without flag 1 the object is let go of as
// bobLinkUnlinkKill does, and with it flag 2 takes its slot out before the
// object moves to mode 2.

#include "src/rel/bob_link_class.inc"

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct BobLinkPoint {
	BobLink link; // 0x00
	s8 mode;      // 0x34
	u8 pad35;
	s16 timer; // 0x36
	RwV3d* at; // 0x38
	RwV3d dir; // 0x3C
	u32 flags; // 0x48
} BobLinkPoint;

typedef struct BobLinkTarget {
	u8 unk00[0x34];
	RwV3d at; // 0x34
} BobLinkTarget;

extern "C" BobLinkTarget lbl_803EA4E8;

typedef struct GameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C180;

extern "C" void bobLinkPointExec(BobLinkPoint* object)
{
	if (lbl_8029C310.mode != 0) {
		object->link.base.signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x1F] != 0 && (object->flags & 8) == 0) {
		return;
	}

	switch (object->mode) {
		case 1: {
			RwV3d* at = object->at;

			lbl_803EA4E8.at.x = at->x;
			lbl_803EA4E8.at.y = at->y;
			lbl_803EA4E8.at.z = at->z;
			if (object->timer > 0 && --object->timer <= 0) {
				if ((object->flags & 1) == 0) {
					bobLinkSlotOut(&object->link);
					if (&object->link == bobLinkCurrent) {
						bobLinkCurrent = NULL;
					}
					object->link.base.signal |= 1;
				} else {
					if (object->flags & 2) {
						bobLinkSlotOut(&object->link);
					}
					object->mode = 2;
				}
			}
			break;
		}
		case 2:
			break;
	}
}
