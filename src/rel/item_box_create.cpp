#include "types.h"

// nItemBox::CreateItemBox (the PS2 build's name): when a team has opened an item
// box and is in mode 3, it picks one of the item panel effects at random
// (rand scaled to a count) and shows it to everyone. The random number is
// converted with the module's shared int-to-float bias (itemBoxBias), whose 8
// bytes of .rodata this unit owns.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

enum EnumTypeItem { ITEM_NONE };

typedef struct ItemBoxTeam {
	u8 unk00[0x34];
	s32 mode; // 0x34
	u8 unk38[0x3];
	s8 character; // 0x3B
} ItemBoxTeam;

extern "C" ItemBoxTeam* lbl_80303DC8[];
extern "C" const f32 itemBoxRandScale[1];
extern "C" const f32 itemBoxRandCount[1];
extern "C" EnumTypeItem itemBoxEffects[];

extern "C" s32 fn_80090B3C();
extern "C" s32 rand();
void ExecuteAndDisplayItempanelEffectForAll(int group, int type, EnumTypeItem item, int data);

namespace nItemBox
{
void CreateItemBox(RwV3d* pos);
}

void nItemBox::CreateItemBox(RwV3d* pos)
{
	s32 team = fn_80090B3C();

	if (team != -1) {
		ItemBoxTeam* object = lbl_80303DC8[team];

		if (object != NULL && object->mode == 3) {
			s32 pick = (s32)(itemBoxRandCount[0] * (itemBoxRandScale[0] * (f32)rand()));

			ExecuteAndDisplayItempanelEffectForAll(
			    team, object->character, itemBoxEffects[pick], 1);
		}
	}
}
