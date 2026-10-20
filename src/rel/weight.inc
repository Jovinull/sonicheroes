// TObjWeight (the PS2 build's name), the weight that drops on the players:
// the fields its matrix and area checks read, SetWeightMatrix, and the area
// check, which inlines SetWeightMatrix and which the weight's code inlines.

#include "MSL_C/math.h"

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct Weight {
	u8 unk00[0xB8];      // 0x00
	s8 kind;             // 0xB8
	u8 unkB9[0x23];      // 0xB9
	RwMatrixTag* matrix; // 0xDC
	u8 unkE0[0x4];       // 0xE0
	RwV3d pos;           // 0xE4
	u8 unkF0[0x4];       // 0xF0
	s32 angle;           // 0xF4
	u8 unkF8[0x4];       // 0xF8
	f32 base;            // 0xFC
	f32 range;           // 0x100
	RwV3d scale;         // 0x104
} Weight;

extern "C" const f32 weightOne[1];
extern "C" const RwV3d AxisY;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" RwMatrixTag* fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);

// builds the weight's matrix once: turned about the Y axis by its angle and
// moved to its position at its base height
inline void SetWeightMatrix(Weight* object)
{
	if (object->matrix == NULL) {
		object->matrix   = new RwMatrixTag;
		RwMatrixTag* out = object->matrix;
		RwMatrixTag matrix;

		fn_80195790(&matrix, &AxisY, weightOne[0] - fn_800D7AE4(object->angle),
		    fn_800D7B00(object->angle), 0);
		RwV3d pos = object->pos;
		pos.y     = object->base;
		fn_80196050(&matrix, &pos, 2);
		fn_80195B5C(out, &matrix);
	}
}

typedef struct WeightPlayerState {
	u8 unk00[0x6]; // 0x00
	s16 flags;     // 0x06
} WeightPlayerState;

extern "C" WeightPlayerState* lbl_802AD090[];
extern "C" void* lbl_802AD070[];
extern "C" const f32 weightHalfDepth[1];
extern "C" const f32 weightHalfWidth[1];
extern "C" const f32 weightTopMargin[1];

extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" s32 fn_800AB32C(void* task);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

// CheckPlayerTrespassArea (the PS2 build's name): builds the weight's matrix
// and answers whether some player stands under the weight: its position seen
// in the weight's frame no higher than the weight's height above its base
// (plus a margin) and within its scaled half width and half depth. With
// `active`, only the players whose state has bit 0 set count.
inline s32 CheckPlayerTrespassArea(Weight* object, s32 active)
{
	RwV3d pos;

	SetWeightMatrix(object);
	for (int i = 0; i < 8; i++) {
		if (fn_8003E2E4(i, 0, &pos, 0) == 0) {
			continue;
		}
		if (active) {
			if (lbl_802AD090[i] == NULL) {
				continue;
			}
			if ((lbl_802AD090[i]->flags & 1) == 0) {
				continue;
			}
		}
		if (fn_800AB32C(lbl_802AD070[i]) != 0) {
			continue;
		}
		fn_8019941C(&pos, &pos, 1, object->matrix);
		if (pos.y > weightTopMargin[0] + (object->pos.y - object->base)) {
			continue;
		}
		if ((f32)__fabs(pos.x) > weightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(pos.z) > weightHalfDepth[0] * object->scale.z) {
			continue;
		}
		return 1;
	}
	return 0;
}
