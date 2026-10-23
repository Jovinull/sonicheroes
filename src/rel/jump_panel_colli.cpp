#include "types.h"

// TObjJumppanel::SetCollisionParameter (the PS2 build's name, by its place in
// the PS2 order; jumpPanelSetCollisionParameter here): the collision shape is
// turned a quarter turn about Y and about Z by the panel's pitch less 0x1200;
// then the range is worked out again.

typedef struct JumpPanelShape {
	u8 unk00[0x28];
	s32 angY; // 0x28
	s32 angZ; // 0x2C
} JumpPanelShape;

typedef struct JumpPanel {
	u8 unk00[0x30];
	u8 colli[0x10];       // 0x30 (C_COLLI)
	JumpPanelShape* info; // 0x40
	u8 unk44[0x90];       // 0x44
	s32 angX;             // 0xD4
} JumpPanel;

extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" void jumpPanelSetCollisionParameter(JumpPanel* object)
{
	if (object->info != NULL) {
		object->info->angY = 0x4000;
		object->info->angZ = object->angX - 0x1200;
		CalcRange__7C_COLLIFv(object->colli);
	}
}
