#include "types.h"

// The checkpoint star's constructor (the PS2 build's ObjCheckpointSubstance;
// checkpointStarCtor here): no checkpoint yet, mode 1, and clones of the star
// and its effect model.

typedef struct RpClump RpClump;
typedef struct Checkpoint Checkpoint;

typedef struct CheckpointStar {
	s32 mode;          // 0x00
	u8 unk04[0x24];    // 0x04
	s16 unk28;         // 0x28
	s16 id;            // 0x2A
	Checkpoint* owner; // 0x2C
	RpClump* model;    // 0x30
	RpClump* effect;   // 0x34
} CheckpointStar;

extern "C" RpClump* checkpointStar;
extern "C" RpClump* checkpointStarEffect;

extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" CheckpointStar* checkpointStarCtor(CheckpointStar* star)
{
	star->unk28 = star->id = 0;
	star->owner            = NULL;
	star->mode             = 1;
	star->model            = fn_80150588(checkpointStar);
	star->effect           = fn_80150588(checkpointStarEffect);
	return star;
}
