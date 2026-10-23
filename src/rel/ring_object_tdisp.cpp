#include "types.h"

// TObjSetRing::TDisp (the PS2 build's name, by its place in the PS2 order;
// ringObjectTDisp here): an active set ring, or one being edited, draws its
// rings (TObjRing::TDisp) while the game is neither paused nor in a demo.

typedef struct SetRing {
	u8 unk00[0x2A];
	s8 active;      // 0x2A
	u8 unk2B[0x25]; // 0x2B
	u8 motion[0x8]; // 0x50 (TObjSetObj)
} SetRing;

extern "C" u8* lbl_8042C180;

extern "C" s32 OnEdit__10TObjSetObjFv(void* motion);
extern "C" void ringTDisp(SetRing* object);

extern "C" void ringObjectTDisp(SetRing* object)
{
	if (object->active == 1 || OnEdit__10TObjSetObjFv(object->motion)) {
		if ((s8)lbl_8042C180[0x20] == 0 && *(s32*)(lbl_8042C180 + 0x40) < 0) {
			ringTDisp(object);
		}
	}
}
