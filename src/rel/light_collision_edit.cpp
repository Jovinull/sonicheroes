#include "types.h"

// The lightCollision object's EditOnChange (fn_3_4EE40 here: the name every module, rel/o_invoke_colli.cpp and
// tools/fix_o_invoke_colli_object.py already use for it): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct LightCollisionParams {
	s8 f00; // 0x00
	s8 f01; // 0x01
	s8 f02; // 0x02
	u8 pad03[0x1];
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} LightCollisionParams;

typedef struct LightCollisionEdit {
	u8 unk00[0x2C];
	LightCollisionParams* params; // 0x2C
} LightCollisionEdit;

extern "C" const char* lightCollisionFieldNames[];
extern "C" const char* lightCollisionFields0[];
extern "C" const char* lightCollisionFields1[];
extern "C" const char* lightCollisionFields2[];
extern "C" const char* lightCollisionFields3[];
extern "C" const char* lightCollisionFields4[];
extern "C" const char* lightCollisionFields5[];

extern "C" const f32 lightCollisionNoSize[1];

extern "C" void fn_3_4EE40(void* object, LightCollisionEdit* edit)
{
	LightCollisionParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 19) {
		params->f00 = 18;
	}
	if (params->f01 < 0) {
		params->f01 = 0;
	}
	if (params->f01 >= 4) {
		params->f01 = 3;
	}
	if (params->f02 < 0) {
		params->f02 = 0;
	}
	if (params->f02 >= 4) {
		params->f02 = 3;
	}
	if (params->f04 < *(limit = lightCollisionNoSize)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = lightCollisionNoSize)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = lightCollisionNoSize)) {
		params->f0C = *limit;
	}
	lightCollisionFieldNames[0] = lightCollisionFields0[params->f00];
	lightCollisionFieldNames[1] = lightCollisionFields1[params->f01];
	lightCollisionFieldNames[2] = lightCollisionFields2[params->f02];
	lightCollisionFieldNames[3] = lightCollisionFields3[params->f02];
	lightCollisionFieldNames[4] = lightCollisionFields4[params->f02];
	lightCollisionFieldNames[5] = lightCollisionFields5[params->f02];
}
