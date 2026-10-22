// TObjFlowerCommon (the PS2 build's class), the flower that carries the
// players up: the fields its members here read.

#ifndef FLOWER_COMMON_INC
#define FLOWER_COMMON_INC

typedef struct RpClump RpClump;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct FlowerShape {
	u8 kind;        // 0x00
	u8 unk01[0x7];  // 0x01
	RwV3d center;   // 0x08
	f32 a, b, c;    // 0x14
	u8 unk20[0x10]; // 0x20
} FlowerShape;      // 0x30, a CCL_INFO

typedef struct FlowerCommon {
	u8 unk000[0x18];     // 0x000
	void** vtable;       // 0x018
	u8 unk01C[0xC];      // 0x01C
	void* frame;         // 0x028, the set object's
	void** setObjVtable; // 0x02C
	u8 colli[0x10];      // 0x030 (C_COLLI)
	FlowerShape* info;   // 0x040
	u8 unk044[0x74];     // 0x044
	s32 kind;            // 0x0B8
	u8 unk0BC[0x1C];     // 0x0BC
	f32 scale;           // 0x0D8
	u8 unk0DC[0x4];      // 0x0DC
	f32 height;          // 0x0E0
	f32 stemRest;        // 0x0E4
	u8 unk0E8[0x4];      // 0x0E8
	s32 stemCount;       // 0x0EC
	u8 unk0F0[0xC];      // 0x0F0
	RpClump* model;      // 0x0FC
	RpClump* worldModel; // 0x100, added to the world
	RpClump* models[3];  // 0x104
} FlowerCommon;

extern "C" const f32 flowerCommonOne[1];
extern "C" const f32 flowerBound2[1];

extern "C" void SetPosition_Stem__16TObjFlowerCommonFif(
    FlowerCommon* flower, s32 index, f32 length);

// Draw_Stem (the PS2 build's name): each whole stem piece, then the part left
// over. Disp inlines it; rel/flower_common_draw_stem.cpp has the out-of-line
// copy.
static inline void flowerDrawStem(FlowerCommon* flower)
{
	int i;

	for (i = 0; i < flower->stemCount; i++) {
		SetPosition_Stem__16TObjFlowerCommonFif(flower, i, flowerCommonOne[0]);
	}
	if (flowerBound2[0] != flower->stemRest) {
		SetPosition_Stem__16TObjFlowerCommonFif(flower, i, flower->stemRest);
	}
}

#endif
