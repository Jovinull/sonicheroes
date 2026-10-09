// TObjS13Cloud1's EditOnChange: the kind in the placement's parameters wraps
// to 0 outside 0-2, the two counts are kept non-negative, and in the stage the
// game state lbl_8029C310 numbers 14 the editor's first field is named after
// the kind. The class is shared through s13_cloud1_class.inc.

#define S13_CLOUD1_CTOR inline
#include "src/rel/s13_cloud1_class.inc"

// The game state lbl_8029C310 points into: the stage number at +0x2C.
struct Cloud1GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
};

extern "C" Cloud1GameState lbl_8029C310;
extern "C" const char* s13Cloud1FieldNames[];
extern "C" const char* s13Cloud1KindNames[3];

void TObjS13Cloud1::EditOnChange(SETDATA_PARAM* data)
{
	S13Cloud1Param* param = (S13Cloud1Param*)data->setBuffer;

	if (param->kind < 0) {
		param->kind = 0;
	}
	if (param->kind >= 3) {
		param->kind = 0;
	}
	if (param->unk2 < 0) {
		param->unk2 = 0;
	}
	if (param->unk4 < 0) {
		param->unk4 = 0;
	}
	if (lbl_8029C310.stage == 14) {
		s13Cloud1FieldNames[0] = s13Cloud1KindNames[param->kind];
	}
}
