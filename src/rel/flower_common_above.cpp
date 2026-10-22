#include "types.h"

// TObjFlowerCommon's GetFlowerAbovePos and SearchAppearObject (the PS2
// build's names, in its order). GetFlowerAbovePos takes a point above the
// flower: the flower's matrix (its position, its heading, raised by its height
// and scaled by its scale) applied to the offset kept in the module's data.
// SearchAppearObject keeps the first placement of the flower's group that
// appears (flag 0x2000000) within reach of that point; it inlines
// GetFlowerAbovePos.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct FlowerParam {
	RwV3d pos;                // 0x00
	u8 unk0C[0xC];            // 0x0C
	u32 flags;                // 0x18
	u8 unk1C[0xE];            // 0x1C
	u8 group;                 // 0x2A
	u8 unk2B[0xD];            // 0x2B
	struct FlowerParam* next; // 0x38
} FlowerParam;

typedef struct FlowerLists {
	u8 unk00[0x30];
	FlowerParam* groups[1]; // 0x30
} FlowerLists;

typedef struct FlowerCommon {
	u8 unk000[0x28];
	FlowerParam* param;  // 0x028
	u8 unk02C[0x94];     // 0x02C
	RwV3d pos;           // 0x0C0
	s32 angX;            // 0x0CC
	s32 angY;            // 0x0D0
	s32 angZ;            // 0x0D4
	f32 scale;           // 0x0D8
	u8 unk0DC[0x4];      // 0x0DC
	f32 height;          // 0x0E0
	u8 unk0E4[0xB0];     // 0x0E4
	FlowerParam* appear; // 0x194
} FlowerCommon;

extern "C" FlowerLists* lbl_8042C298;
extern "C" const RwV3d AxisY;
extern "C" const f32 flowerCommonOne[1];
extern "C" const f32 flowerBound2[1];
// the offset of the point above the flower
extern "C" f32 flowerAboveX;
extern "C" f32 flowerAboveY;
extern "C" f32 flowerAboveZ;
// how near the point a placement has to be
extern "C" f32 flowerAppearReach;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" void fn_80195E44(RwMatrixTag* matrix, RwV3d* scale, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);
f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

extern "C" void GetFlowerAbovePos__16TObjFlowerCommonFR5RwV3d(FlowerCommon* flower, RwV3d& out)
{
	RwMatrixTag matrix;
	RwV3d offset;
	RwV3d scale;

	fn_80196050(&matrix, &flower->pos, 0);
	fn_80195790(&matrix, &AxisY, flowerCommonOne[0] - fn_800D7AE4(flower->angY),
	    fn_800D7B00(flower->angY), 1);
	offset.x = offset.z = flowerBound2[0];
	offset.y            = flower->height;
	fn_80196050(&matrix, &offset, 1);
	scale.x = scale.y = scale.z = flower->scale;
	fn_80195E44(&matrix, &scale, 1);
	offset.x = flowerAboveX;
	offset.y = flowerAboveY;
	offset.z = flowerAboveZ;
	CalcPoint(&matrix, &offset, &out);
}

extern "C" void SearchAppearObject__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	FlowerParam* p;

	for (p = lbl_8042C298->groups[flower->param->group]; p != NULL; p = p->next) {
		if (p->flags & 0x2000000) {
			RwV3d above;

			GetFlowerAbovePos__16TObjFlowerCommonFR5RwV3d(flower, above);
			if (Distance2P2P(&p->pos, &above) < flowerAppearReach) {
				flower->appear = p;
				return;
			}
		}
	}
}
