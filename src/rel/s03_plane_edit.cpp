#include "types.h"

// TObjS03Plane's EditOnChange (s03PlaneEditOnChange here; the class is the one
// whose vtable holds it): it keeps each edited parameter within its bounds. The
// body of s01ObjectBaseEditOnChange (rel/o_s01_base.cpp), with the module's own
// tables. The fields are named by their offsets (written with
// notes/tools/clampgen.py).

typedef struct S03PlaneParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
} S03PlaneParams;

typedef struct S03PlaneEdit {
	u8 unk00[0x2C];
	S03PlaneParams* params; // 0x2C
} S03PlaneEdit;

extern "C" const f32 s03PlaneBound0[1];

extern "C" void s03PlaneEditOnChange(void* object, S03PlaneEdit* edit)
{
	S03PlaneParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = s03PlaneBound0)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = s03PlaneBound0)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = s03PlaneBound0)) {
		params->f08 = *limit;
	}
}
