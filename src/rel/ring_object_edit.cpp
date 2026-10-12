#include "types.h"

// The ringObject object's EditOnChange (ringObjectEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct RingObjectParams {
	s16 f00; // 0x00
	s16 f02; // 0x02
	f32 f04; // 0x04
	f32 f08; // 0x08
} RingObjectParams;

typedef struct RingObjectEdit {
	u8 unk00[0x2C];
	RingObjectParams* params; // 0x2C
} RingObjectEdit;

extern "C" const char* ringObjectFieldNames[];
extern "C" const char* ringObjectFields0[];
extern "C" const char* ringObjectFields1[];
extern "C" const char* ringObjectFields2[];
extern "C" const char* ringObjectFields3[];

extern "C" const f32 scrollRingStopped[1];
extern "C" const f32 ringObjectBound1[1];

extern "C" void ringObjectEditOnChange(void* object, RingObjectEdit* edit)
{
	RingObjectParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 5) {
		params->f00 = 4;
	}
	if (params->f02 < 0) {
		params->f02 = 0;
	}
	if (params->f02 > 127) {
		params->f02 = 127;
	}
	if (params->f04 < *(limit = scrollRingStopped)) {
		params->f04 = *limit;
	}
	if (params->f04 > *(limit = ringObjectBound1)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = scrollRingStopped)) {
		params->f08 = *limit;
	}
	if (params->f08 > *(limit = ringObjectBound1)) {
		params->f08 = *limit;
	}
	ringObjectFieldNames[0] = ringObjectFields0[params->f00];
	ringObjectFieldNames[1] = ringObjectFields1[params->f00];
	ringObjectFieldNames[2] = ringObjectFields2[params->f00];
	ringObjectFieldNames[3] = ringObjectFields3[params->f00];
}
