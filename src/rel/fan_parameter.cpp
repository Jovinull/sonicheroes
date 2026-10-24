#include "types.h"

// TObjFan's SetCollisionParameter and SetParameter (the PS2 build's names;
// fanSetCollisionParameter and fanSetParameter here). SetParameter takes the placement: position and heading (no pitch or
// roll), the kind, the flags, the column's height, sizes and strength over
// their base values, and whether the fan spins (the placement's flag clear).
// SetCollisionParameter sizes the collision to the height.

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct FanParams {
	f32 height;    // 0x00
	f32 width;     // 0x04
	f32 depth;     // 0x08
	f32 strength;  // 0x0C
	s8 kind;       // 0x10
	u8 unk11;      // 0x11
	u8 pad12[0x2]; // 0x12
	f32 reach;     // 0x14
	s8 flag;       // 0x18
} FanParams;

typedef struct FanFrame {
	RwV3d pos;         // 0x00
	sAngle ang;        // 0x0C
	u32 flags;         // 0x18
	u8 unk1C[0x10];    // 0x1C
	FanParams* params; // 0x2C
} FanFrame;

typedef struct CclInfo {
	u8 unk00[0x14];
	f32 a; // 0x14
} CclInfo;

typedef struct Fan {
	u8 unk00[0x28];  // 0x00
	FanFrame* frame; // 0x28, the set object's
	u8 unk2C[0x4];   // 0x2C
	u8 colli[0x10];  // 0x30 (C_COLLI)
	CclInfo* info;   // 0x40
	u8 unk44[0x78];  // 0x44
	u8 kind;         // 0xBC
	u8 unkBD;        // 0xBD
	u8 padBE[0x2];   // 0xBE
	RwV3d pos;       // 0xC0
	sAngle ang;      // 0xCC
	u8 unkD8[0x8];   // 0xD8
	f32 height;      // 0xE0
	f32 reach;       // 0xE4
	f32 strength;    // 0xE8
	f32 width;       // 0xEC
	f32 depth;       // 0xF0
	s32 spinning;    // 0xF4
	RpClump* model;  // 0xF8
} Fan;

extern "C" const f32 fanBaseHeight[1];
extern "C" const f32 fanBaseSize[1];
extern "C" const f32 fanBaseStrength[1];
extern "C" const f32 fanOne[1];

extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" void fanSetCollisionParameter(Fan* object)
{
	object->info->a = object->height;
	CalcRange__7C_COLLIFv(object->colli);
}

extern "C" void fanSetParameter(Fan* object)
{
	FanParams* params = object->frame->params;

	object->pos   = object->frame->pos;
	object->ang   = object->frame->ang;
	object->kind  = params->kind;
	object->ang.x = 0;
	object->ang.z = 0;
	object->unkBD = params->unk11;

	object->height   = fanBaseHeight[0] + params->height;
	object->width    = fanBaseSize[0] + params->width;
	object->depth    = fanBaseSize[0] + params->depth;
	object->strength = fanBaseStrength[0] + params->strength;
	object->reach    = fanOne[0] + params->reach;
	object->spinning = (bool)(params->flag == 0);
}
