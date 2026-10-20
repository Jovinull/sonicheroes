#include "types.h"

// TObjWeightExtSub::Exec (the PS2 build's name; weightExtExec here): the
// breakable weight's piece follows its weight. Unless the weight is in mode 5
// it checks for damage, moves its collision to the weight's position and
// angles (keeping the previous position) and enters it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct WeightExtOwner {
	u8 unk000[0x100]; // 0x000
	s32 mode;         // 0x100
	RwV3d pos;        // 0x104
	sAngle ang;       // 0x110
} WeightExtOwner;

typedef struct WeightExt {
	u8 unk00[0x28];        // 0x00
	u8 colli[0x60];        // 0x28 (C_COLLI)
	RwV3d colliPos;        // 0x88
	sAngle colliAng;       // 0x94
	u8 unkA0[0x4];         // 0xA0
	RwV3d prePos;          // 0xA4
	WeightExtOwner* owner; // 0xB0
} WeightExt;

extern "C" void weightExtCheckDamage(WeightExt* object);
extern "C" void Entry__7C_COLLIFv(void* colli);

extern "C" void weightExtExec(WeightExt* object)
{
	if (object->owner->mode != 5) {
		weightExtCheckDamage(object);
		WeightExtOwner* owner = object->owner;
		object->prePos        = object->colliPos;
		object->colliPos      = owner->pos;
		object->colliAng      = owner->ang;
		Entry__7C_COLLIFv(object->colli);
	}
}
