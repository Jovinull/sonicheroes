// Places a camera between two path points by the player's distance to them (HYPOTHESIS; names
// inferred): with the current player's position (0x40), weights the targets at 0x38 and 0x5C of
// the path node by the distances to the node's points at 0x68 and 0x50 (the nearer point weighs
// more), stores the blended target at 0x10 of the camera, the player position at 0x34 and the
// node value at 0x4C at 0x24, and clears the words at 0x0, 0x4, 0x8 and 0xC. Built with the
// game-unit flags and -fp_contract off.
#include "game/matrix.h"

struct Player801364C8 {
	u8 pad0[0x40];
	RwV3d position; // 0x40
};

struct Node801364C8 {
	u8 pad0[0x38];
	RwV3d targetA; // 0x38
	u8 pad44[0x4C - 0x44];
	s32 value;     // 0x4C
	RwV3d pointA;  // 0x50
	RwV3d targetB; // 0x5C
	RwV3d pointB;  // 0x68
};

struct Source801364C8 {
	u8 pad0[0x10];
	Node801364C8* node; // 0x10
};

struct Camera801364C8 {
	s32 value0;   // 0x0
	s32 value4;   // 0x4
	s32 value8;   // 0x8
	s32 valueC;   // 0xC
	RwV3d target; // 0x10
	u8 pad1C[0x24 - 0x1C];
	s32 value24; // 0x24
	u8 pad28[0x34 - 0x28];
	RwV3d position; // 0x34
};

extern "C" {
extern Player801364C8* lbl_80303DC8[];
extern s32 lbl_8042C1FC;
extern f32 lbl_8042F060; // 1.0f
// HYPOTHESIS: RwV3dLength.
f32 fn_801991B4(const RwV3d* vector);

void fn_801364C8(Camera801364C8* camera, Source801364C8* source)
{
	Node801364C8* node      = source->node;
	Player801364C8** player = &lbl_80303DC8[lbl_8042C1FC];
	RwV3d delta;
	f32 distanceA;
	f32 distanceB;
	f32 weightA;
	f32 weightB;

	delta.x   = (*player)->position.x - node->pointA.x;
	delta.y   = (*player)->position.y - node->pointA.y;
	delta.z   = (*player)->position.z - node->pointA.z;
	distanceA = fn_801991B4(&delta);
	delta.x   = (*player)->position.x - node->pointB.x;
	delta.y   = (*player)->position.y - node->pointB.y;
	delta.z   = (*player)->position.z - node->pointB.z;
	distanceB = fn_801991B4(&delta);
	weightA   = distanceB / (distanceA + distanceB);
	weightB   = lbl_8042F060 - weightA;

	camera->value0   = 0;
	camera->value4   = 0;
	camera->target.x = node->targetA.x * weightA + node->targetB.x * weightB;
	camera->target.y = node->targetA.y * weightA + node->targetB.y * weightB;
	camera->target.z = node->targetA.z * weightA + node->targetB.z * weightB;
	camera->position = (*player)->position;
	camera->value24  = node->value;
	camera->value8   = 0;
	camera->valueC   = 0;
}
}
