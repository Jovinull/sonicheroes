#include "types.h"

// The no-input collision's SetParameter (the PS2 build's name;
// noInputCollisionSetParameter here): it takes the placement's position and
// angle, and from its parameters the box size and the kind.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct NoInputAngle {
	s32 x, y, z;
} NoInputAngle;

typedef struct NoInputParams {
	s32 kind;   // 0x00
	RwV3d size; // 0x04
} NoInputParams;

typedef struct NoInputFrame {
	RwV3d pos;             // 0x00
	NoInputAngle ang;      // 0x0C
	u8 unk18[0x14];        // 0x18
	NoInputParams* params; // 0x2C
} NoInputFrame;

typedef struct NoInputCollision {
	u8 base[0x28];       // 0x00
	NoInputFrame* frame; // 0x28
	u8 unk2C[0x8C];      // 0x2C
	s32 kind;            // 0xB8
	u8 unkBC[0x4];       // 0xBC
	RwV3d pos;           // 0xC0
	NoInputAngle ang;    // 0xCC
	RwV3d size;          // 0xD8
} NoInputCollision;

extern "C" void noInputCollisionSetParameter(NoInputCollision* object)
{
	NoInputParams* params = object->frame->params;
	object->pos           = object->frame->pos;
	object->ang           = object->frame->ang;
	object->size          = params->size;
	object->kind          = params->kind;
}
