#include "types.h"

// TObjFlowerCommon's CheckInCase and SetParameter (the PS2 build's names, by
// their place in the PS2 order). CheckInCase looks for a hit of kind 0x13 on
// the flower's collision: with one the collision's first shape gets kind 0
// and the answer is yes, without it kind 0x1D. SetParameter takes the
// placement: position and heading (no pitch or roll), the kind, the scale
// over its base and the second value.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct FlowerParams {
	s8 kind; // 0x00
	u8 pad1[3];
	f32 scale; // 0x04
	f32 unk8;  // 0x08
} FlowerParams;

typedef struct FlowerFrame {
	RwV3d pos;            // 0x00
	sAngle ang;           // 0x0C
	u8 unk18[0x14];       // 0x18
	FlowerParams* params; // 0x2C
} FlowerFrame;

typedef struct FlowerHit {
	u8 unk0[0x4];
	void* hitter; // 0x04
} FlowerHit;

typedef struct FlowerCommon {
	u8 unk00[0x28];     // 0x00
	FlowerFrame* frame; // 0x28, the set object's
	u8 unk2C[0x4];      // 0x2C
	u8 colli[0x10];     // 0x30 (C_COLLI)
	u8* info;           // 0x40, the collision's shapes
	u8 unk44[0x74];     // 0x44
	s32 kind;           // 0xB8
	u8 unkBC[0x4];      // 0xBC
	RwV3d pos;          // 0xC0
	sAngle ang;         // 0xCC
	f32 scale;          // 0xD8
	f32 unkDC;          // 0xDC
} FlowerCommon;

extern "C" u8 lbl_8042C1A4[];
extern "C" const f32 flowerCommonOne[1];

extern "C" void fn_80021824(void* world);
extern "C" FlowerHit* fn_80020BD8(void* colli, s32 kind);

static inline void* flowerHitter(FlowerHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" s32 CheckInCase__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	if (flower->info == NULL) {
		return 0;
	}
	fn_80021824(lbl_8042C1A4);
	if (flowerHitter(fn_80020BD8(flower->colli, 0x13)) != NULL) {
		flower->info[0] = 0;
		return 1;
	}
	flower->info[0] = 0x1D;
	return 0;
}

extern "C" void SetParameter__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	FlowerParams* params = flower->frame->params;

	flower->pos   = flower->frame->pos;
	flower->ang   = flower->frame->ang;
	flower->ang.x = flower->ang.z = 0;
	flower->kind                  = params->kind;
	flower->scale                 = flowerCommonOne[0] + params->scale;
	flower->unkDC                 = params->unk8;
}
