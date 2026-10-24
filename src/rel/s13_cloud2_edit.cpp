// TObjS13Cloud2's EditOnChange, the body of TObjS13Cloud1's
// (rel/s13_cloud1_edit.cpp) with the module's own tables: the kind in the
// placement's parameters wraps to 0 outside 0-2, the two counts are kept
// non-negative, and in the stage the game state lbl_8029C310 numbers 14 the
// editor's first field is named after the kind.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S13Cloud2Param {
	s8 kind;  // 0x00
	u8 pad01; // 0x01
	s16 unk2; // 0x02
	s16 unk4; // 0x04
};

// Exec comes first so that it is the key function and no unit of ours emits
// the vtable
class TObjS13Cloud2 : public TObject, public TObjSetObj
{
public:
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

// The game state lbl_8029C310 points into: the stage number at +0x2C.
struct Cloud2GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
};

extern "C" Cloud2GameState lbl_8029C310;
extern "C" const char* s13Cloud2FieldNames[];
extern "C" const char* s13Cloud2KindNames[3];

void TObjS13Cloud2::EditOnChange(SETDATA_PARAM* data)
{
	S13Cloud2Param* param = (S13Cloud2Param*)data->setBuffer;

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
		s13Cloud2FieldNames[0] = s13Cloud2KindNames[param->kind];
	}
}
