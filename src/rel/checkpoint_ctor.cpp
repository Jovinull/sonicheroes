#include "types.h"

// The checkpoint's constructor (checkpointCtor here), called by the factory in
// rel/checkpoint_hooks.cpp.
//
// It takes the placement's position, angle and first parameter, clears its
// state, and makes the star that floats over the post: a 0x94-byte block with
// clumps of the star and of its effect, placed 8 above the post with the post's
// angle and no velocity, and moved once (checkpointStarMove). A checkpoint
// already passed (condition bit 0x10000) starts with the star in state 3.

typedef struct TObject {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} TObject;                 // 0x28

typedef struct Vec3 {
	f32 x, y, z;
} Vec3;

typedef struct Angle {
	s32 x, y, z;
} Angle;

typedef struct Frame {
	Vec3 pos;       // 0x00
	Angle ang;      // 0x0C
	u32 condition;  // 0x18
	u8 unk1C[0x10]; // 0x1C
	s16* params;    // 0x2C
} Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

struct Checkpoint;

typedef struct CheckpointStar {
	s32 state;                // 0x00
	Vec3 pos;                 // 0x04
	Angle ang;                // 0x10
	Vec3 velocity;            // 0x1C
	s16 unk28;                // 0x28
	s16 unk2A;                // 0x2A
	struct Checkpoint* owner; // 0x2C
	void* clump;              // 0x30
	void* effect;             // 0x34
	u8 unk38[0x40];           // 0x38
	f32 unk78;                // 0x78
	s32 unk7C;                // 0x7C
	s32 unk80;                // 0x80
	f32 unk84;                // 0x84
	s32 unk88;                // 0x88
	s32 unk8C;                // 0x8C
	s32 unk90;                // 0x90
} CheckpointStar;             // 0x94

typedef struct Checkpoint {
	TObject base;         // 0x00
	Motion motion;        // 0x28
	s8 unk30;             // 0x30
	u8 pad31;             // 0x31
	s16 unk32;            // 0x32
	u8 pad34[4];          // 0x34
	Vec3 pos;             // 0x38
	Angle ang;            // 0x44
	CheckpointStar* star; // 0x50
	f32 unk54;            // 0x54
	Vec3 unk58;           // 0x58
	s32 unk64;            // 0x64
	s32 unk68;            // 0x68
	s32 unk6C;            // 0x6C
	s32 unk70;            // 0x70
	u8 unk74[8];          // 0x74
} Checkpoint;             // 0x7C

extern "C" void* checkpointVtable[];
extern "C" const char* checkpointClassName;
extern "C" const f32 checkpointZero[1];
extern "C" const f32 checkpointOne[1];
extern "C" const f32 checkpointStarScale[1];
extern "C" Vec3 checkpointStarOffset;
extern "C" void* checkpointStar;
extern "C" void* checkpointStarEffect;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(Motion* motion);
extern "C" void* __nw__FUl(u32 size);
extern "C" void* fn_80150588(void* model);
extern "C" void checkpointStarMove(CheckpointStar* star);

extern "C" Checkpoint* checkpointCtor(Checkpoint* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	object->base.vtable     = checkpointVtable;
	object->motion.vtable   = checkpointVtable + 0xB;
	object->base.className  = checkpointClassName;
	object->base.objectSize = 0x7C;
	object->pos             = object->motion.frame->pos;
	object->ang             = object->motion.frame->ang;
	object->unk32           = object->motion.frame->params[0];
	object->unk58.z = object->unk58.y = object->unk58.x = checkpointZero[0];
	object->unk70                                       = 0;
	object->unk64                                       = 0;
	object->unk68                                       = 0;
	object->unk6C                                       = 0;
	object->unk54                                       = checkpointOne[0];
	object->unk30                                       = -1;

	CheckpointStar* star = (CheckpointStar*)__nw__FUl(0x94);
	if (star != NULL) {
		star->unk2A  = 0;
		star->unk28  = 0;
		star->owner  = NULL;
		star->state  = 1;
		star->clump  = fn_80150588(checkpointStar);
		star->effect = fn_80150588(checkpointStarEffect);
	}
	object->star = star;

	star        = object->star;
	star->owner = object;
	star->unk2A = 0;
	star->state = 1;
	star->unk78 = checkpointOne[0];
	star->unk84 = checkpointStarScale[0];
	star->unk7C = 0;
	star->unk80 = 0;
	star->unk88 = 0;
	star->unk8C = 0;
	star->unk90 = 0;
	star->pos   = star->owner->pos;
	star->pos.y += checkpointStarOffset.y;
	star->ang        = star->owner->ang;
	star->velocity.x = star->velocity.y = star->velocity.z = checkpointZero[0];
	checkpointStarMove(star);

	if (object->motion.frame->condition & 0x10000) {
		object->star->state = 3;
		object->unk54       = checkpointZero[0];
		object->star->unk78 = checkpointZero[0];
	}
	object->unk74[0] = 0;
	object->unk74[1] = 0;
	object->unk74[2] = 0;
	object->unk74[3] = 0;
	object->unk74[4] = 0;
	object->unk74[5] = 0;
	object->unk74[6] = 0;
	object->unk74[7] = 0;
	return object;
}
