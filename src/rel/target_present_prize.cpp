#include "types.h"

// TObjTarget::PresentPrize (the PS2 build's name, by its place in the PS2
// order; targetPresentPrize here): the team that hit the target gets a ring
// panel by the score (7 for the bull's-eye, 5 for a hit, 1 otherwise) shown
// over its leader, and the target's placement is marked done.

typedef enum EnumTypeItem { ITEM_COUNT = 13 } EnumTypeItem;

typedef struct TargetTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[4]; // 0x110
} TargetTeam;

typedef struct TargetFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} TargetFrame;

typedef struct Target {
	u8 unk00[0x28];
	TargetFrame* frame; // 0x28, the set object's
	u8 unk2C[0x91];     // 0x2C
	s8 holder;          // 0xBD
	u8 unkBE[0x2];      // 0xBE
	s32 score;          // 0xC0
} Target;

extern "C" TargetTeam* lbl_80303DC8[];

void ExecuteAndDisplayItempanelEffectForAll(int group, int type, EnumTypeItem item, int data);

extern "C" void targetPresentPrize(Target* object)
{
	if (object->holder != -1) {
		EnumTypeItem item;

		switch (object->score) {
			case 2:
				item = (EnumTypeItem)5;
				break;
			case 1:
				item = (EnumTypeItem)7;
				break;
			case 0:
			default:
				item = (EnumTypeItem)1;
				break;
		}
		ExecuteAndDisplayItempanelEffectForAll(object->holder,
		    lbl_80303DC8[object->holder]->members[lbl_80303DC8[object->holder]->leader], item, 0);
		object->frame->flags |= 0x10000;
	}
}
