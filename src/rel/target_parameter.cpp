#include "types.h"

// TObjTarget::SetParameter (the PS2 build's name, by its place in the PS2
// order; targetSetParameter here): the placement's position and angle, and
// the target's kind.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct TargetFrame {
	RwV3d pos;      // 0x00
	sAngle ang;     // 0x0C
	u8 unk18[0x14]; // 0x18
	u8* params;     // 0x2C
} TargetFrame;

typedef struct Target {
	u8 unk00[0x28];
	TargetFrame* frame; // 0x28, the set object's
	u8 unk2C[0x90];     // 0x2C
	u8 kind;            // 0xBC
	u8 unkBD[0xB];      // 0xBD
	RwV3d pos;          // 0xC8
	sAngle ang;         // 0xD4
} Target;

extern "C" void targetSetParameter(Target* object)
{
	u8* params   = object->frame->params;
	object->pos  = object->frame->pos;
	object->ang  = object->frame->ang;
	object->kind = params[0];
}
