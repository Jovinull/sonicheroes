#include "types.h"

// The bobJumpCollision object's EditOnChange (EditOnChange__20TObjBobJumpCollisionFP13SETDATA_PARAM here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct BobJumpCollisionParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
} BobJumpCollisionParams;

typedef struct BobJumpCollisionEdit {
	u8 unk00[0x2C];
	BobJumpCollisionParams* params; // 0x2C
} BobJumpCollisionEdit;

extern "C" const f32 bobJumpCollisionBound0[1];

extern "C" void EditOnChange__20TObjBobJumpCollisionFP13SETDATA_PARAM(
    void* object, BobJumpCollisionEdit* edit)
{
	BobJumpCollisionParams* params = edit->params;
	const f32* limit;

	if (params->f00 < *(limit = bobJumpCollisionBound0)) {
		params->f00 = *limit;
	}
	if (params->f04 < *(limit = bobJumpCollisionBound0)) {
		params->f04 = *limit;
	}
	if (params->f08 < *(limit = bobJumpCollisionBound0)) {
		params->f08 = *limit;
	}
	if (params->f0C < *(limit = bobJumpCollisionBound0)) {
		params->f0C = *limit;
	}
}
