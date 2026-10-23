#include "types.h"

// The checkpoint star's destructor, Done and Init (the PS2 build's
// ObjCheckpointSubstance; checkpointStarDtor and so on here, as the family's
// other units name the star). The destructor releases the star and effect
// models; Init ties the star to its checkpoint, puts it above the checkpoint
// with its heading and places it; Done marks it finished (mode 3). The
// constructor is rel/checkpoint_star_ctor.cpp (Init copies structs, which
// moves it to the end of its object).

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct Checkpoint {
	u8 unk00[0x38];
	RwV3d pos;  // 0x38
	sAngle ang; // 0x44
} Checkpoint;

typedef struct CheckpointStar {
	s32 mode;          // 0x00
	RwV3d pos;         // 0x04
	sAngle ang;        // 0x10
	RwV3d spin;        // 0x1C
	s16 unk28;         // 0x28
	s16 id;            // 0x2A
	Checkpoint* owner; // 0x2C
	RpClump* model;    // 0x30
	RpClump* effect;   // 0x34
	u8 unk38[0x40];    // 0x38
	f32 alpha;         // 0x78
	s32 unk7C;         // 0x7C
	s32 unk80;         // 0x80
	f32 scale;         // 0x84
	s32 unk88;         // 0x88
	s32 unk8C;         // 0x8C
	s32 unk90;         // 0x90
} CheckpointStar;

extern "C" const f32 checkpointZero[1];
extern "C" const f32 checkpointOne[1];
extern "C" const f32 checkpointStarScale[1];
extern "C" RwV3d checkpointStarOffset;

extern "C" void fn_80150958(RpClump* clump);
extern "C" void checkpointStarMove(CheckpointStar* star);
void operator delete(void* p);

extern "C" CheckpointStar* checkpointStarDtor(CheckpointStar* star, s16 flags)
{
	if (star != NULL) {
		if (star->model != NULL) {
			fn_80150958(star->model);
			star->model = NULL;
		}
		if (star->effect != NULL) {
			fn_80150958(star->effect);
			star->effect = NULL;
		}
		if (flags > 0) {
			operator delete(star);
		}
	}
	return star;
}

extern "C" void checkpointStarDone(CheckpointStar* star)
{
	star->mode = 3;
}

extern "C" void checkpointStarInit(CheckpointStar* star, Checkpoint* owner, s16 id)
{
	star->owner = owner;
	star->id    = id;
	star->mode  = 1;
	star->alpha = checkpointOne[0];
	star->scale = checkpointStarScale[0];
	star->unk7C = 0;
	star->unk80 = 0;
	star->unk88 = 0;
	star->unk8C = 0;
	star->unk90 = 0;
	star->pos   = star->owner->pos;
	star->pos.y += checkpointStarOffset.y;
	star->ang    = star->owner->ang;
	star->spin.x = star->spin.y = star->spin.z = checkpointZero[0];
	checkpointStarMove(star);
}
