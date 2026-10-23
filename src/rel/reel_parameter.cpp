#include "types.h"

// TObjReel::SetParameter (the PS2 build's name, by its place in the PS2
// order; reelSetParameter here): the placement's position and angle, the
// reel's length, its kind (kind 0 starts wound in, kind 1 let out to its
// length; both kept as the current and target lengths), the turn speed as an
// angle and the last value.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct ReelParams {
	f32 length; // 0x00
	f32 speed;  // 0x04
	f32 unk8;   // 0x08
	s16 kind;   // 0x0C
} ReelParams;

typedef struct ReelFrame {
	RwV3d pos;          // 0x00
	sAngle ang;         // 0x0C
	u8 unk18[0x14];     // 0x18
	ReelParams* params; // 0x2C
} ReelFrame;

typedef struct Reel {
	u8 unk00[0x28];
	ReelFrame* frame; // 0x28, the set object's
	u8 unk2C[0x90];   // 0x2C
	s8 kind;          // 0xBC
	u8 unkBD[0x3];    // 0xBD
	f32 current;      // 0xC0
	f32 target;       // 0xC4
	f32 length;       // 0xC8
	u8 unkCC[0x4];    // 0xCC
	s32 speed;        // 0xD0
	f32 unkD4;        // 0xD4
	u8 unkD8[0x4];    // 0xD8
	RwV3d pos;        // 0xDC
	sAngle ang;       // 0xE8
} Reel;

extern "C" const f32 reelZero[1];
extern "C" const f32 reelAngleScale[1];

extern "C" void reelSetParameter(Reel* object)
{
	object->pos        = object->frame->pos;
	object->ang        = object->frame->ang;
	ReelParams* params = object->frame->params;
	object->length     = params->length;
	object->kind       = params->kind;
	switch (object->kind) {
		case 0:
			object->current = reelZero[0];
			break;
		case 1:
			object->current = object->length;
			break;
	}
	object->target = object->current;
	object->speed  = reelAngleScale[0] * params->speed;
	object->unkD4  = params->unk8;
}
