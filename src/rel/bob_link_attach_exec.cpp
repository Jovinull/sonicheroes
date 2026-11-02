#include "types.h"

// The exec step of the special stages' first sled link class
// (bobLinkAttachExec here; the class has no PS2 name), in stage01D and
// stage07D. It asks to be killed when the game leaves its play mode and waits
// while the game is paused unless flag 8 lets it run. In mode 1 it counts its
// timer down; at zero, without flag 1 it lets go of the object as
// bobLinkUnlinkKill does, and with it flag 2 takes its slot out before the
// object moves to mode 2.

#include "src/rel/bob_link_class.inc"

typedef struct BobLinkAttach {
	BobLink link; // 0x00
	s8 mode;      // 0x34
	u8 pad35;
	s16 timer; // 0x36
	u8 unk38[0x18];
	u32 flags; // 0x50
} BobLinkAttach;

typedef struct GameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C180;

extern "C" void bobLinkAttachExec(BobLinkAttach* object)
{
	if (lbl_8029C310.mode != 0) {
		object->link.base.signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x1F] != 0 && (object->flags & 8) == 0) {
		return;
	}

	switch (object->mode) {
		case 1:
			if (object->timer > 0) {
				object->timer--;
			}
			if (object->timer <= 0) {
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
		case 2:
			break;
	}
}
