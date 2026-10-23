#include "types.h"

// TObjHintColli's IsEverybodyNearby and TDisp (the PS2 build's names, by
// their place in the PS2 order). IsEverybodyNearby answers whether the team's
// count at 0x120 is 3. TDisp, while the debug display (the game state's byte
// at 5) is on, draws the hint area with render states 0xA, 0xB and 0x14 set
// to 2, 2 and 1 (the old values put back after) and the placement's lights.

typedef struct RpClump RpClump;

typedef struct HintColliTeam {
	u8 unk000[0x120];
	s8 nearby; // 0x120
} HintColliTeam;

typedef struct HintColliFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} HintColliFrame;

typedef struct HintColli {
	u8 unk000[0x28];
	HintColliFrame* frame; // 0x028, the set object's
	u8 unk02C[0xD4];       // 0x02C
	RpClump* model;        // 0x100
} HintColli;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

extern "C" u8* lbl_8042C180;
extern "C" HintColliTeam* lbl_80303DC8[];
extern "C" CLIGHT lbl_802D5E80;

extern "C" void fn_80194294(s32 state, s32* value);
extern "C" void fn_80194234(s32 state, s32 value);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" u8 IsEverybodyNearby__13TObjHintColliFi(HintColli* object, s32 team)
{
	return lbl_80303DC8[team]->nearby == 3;
}

extern "C" void TDisp__13TObjHintColliFv(HintColli* object)
{
	if ((s8)lbl_8042C180[5] != 0) {
		s32 state0A;
		s32 state0B;
		s32 state14;

		fn_80194294(0xA, &state0A);
		fn_80194294(0xB, &state0B);
		fn_80194294(0x14, &state14);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 2);
		fn_80194234(0x14, 1);
		lbl_802D5E80.SetCurrentNum(((object->frame->flags & 0x1C0000) >> 18) + 4);
		lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
		fn_8014FF2C(object->model);
		fn_80194234(0x14, state14);
		fn_80194234(0xA, state0A);
		fn_80194234(0xB, state0B);
	}
}
