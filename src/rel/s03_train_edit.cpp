#include "types.h"

// TObjS03Train's EditOnChange (s03TrainEditOnChange here; the class is the one
// whose vtable holds it): it keeps each edited parameter within its bounds. The
// body of s01ObjectBaseEditOnChange (rel/o_s01_base.cpp), with the module's own
// tables. The fields are named by their offsets (written with
// notes/tools/clampgen.py).

typedef struct S03TrainParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
} S03TrainParams;

typedef struct S03TrainEdit {
	u8 unk00[0x2C];
	S03TrainParams* params; // 0x2C
} S03TrainEdit;

extern "C" const f32 s03TrainZero[1];

extern "C" void s03TrainEditOnChange(void* object, S03TrainEdit* edit)
{
	S03TrainParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = s03TrainZero)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = s03TrainZero)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s03TrainZero)) {
		params->f08 = *limit;
	}
}
