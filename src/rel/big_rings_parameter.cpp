#include "types.h"

// TObjBigrings::SetParameter (the PS2 build's name, by its place in the PS2
// order; bigRingsSetParameter here): the placement's position and angle, the
// type, the speed over its base, the no-control time and the scale.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct BigRingsParams {
	s16 type;      // 0x00
	u16 noconTime; // 0x02
	f32 speed;     // 0x04
	f32 scale;     // 0x08
} BigRingsParams;

typedef struct BigRingsFrame {
	RwV3d pos;              // 0x00
	sAngle ang;             // 0x0C
	u8 unk18[0x14];         // 0x18
	BigRingsParams* params; // 0x2C
} BigRingsFrame;

typedef struct BigRings {
	u8 unk00[0x28];
	BigRingsFrame* frame; // 0x28, the set object's
	u8 unk2C[0x8];        // 0x2C
	s8 type;              // 0x34
	u8 unk35[0x3];        // 0x35
	s16 noconTime;        // 0x38
	u8 unk3A[0x2];        // 0x3A
	f32 speed;            // 0x3C
	RwV3d pos;            // 0x40
	sAngle ang;           // 0x4C
	u8 unk58[0xC];        // 0x58
	f32 scale;            // 0x64
} BigRings;

extern "C" const f32 bigRingsBaseSpeed[1];

extern "C" void bigRingsSetParameter(BigRings* object)
{
	object->pos            = object->frame->pos;
	object->ang            = object->frame->ang;
	BigRingsParams* params = object->frame->params;
	object->type           = params->type;
	object->speed          = bigRingsBaseSpeed[0] + params->speed;
	object->noconTime      = params->noconTime;
	object->scale          = params->scale;
}
