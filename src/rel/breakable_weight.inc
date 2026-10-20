// TObjWeightExt (the PS2 build's name), the breakable weight: the fields its
// matrix and area checks read, and its copies of TObjWeight's SetWeightMatrix
// and CheckPlayerTrespassArea (rel/weight.inc), the same code over this
// class's layout and constants.

#include "MSL_C/math.h"

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct BreakableWeight {
	u8 unk00[0x30]; // 0x00
	u8 colli[0x88]; // 0x30 (C_COLLI)
	union {         // 0xB8
		u8 replace; // the OBJ_ReplacePlayer part, which has no fields
		s8 kind;
	};
	u8 unkB9[0x1F];      // 0xB9
	s32 rider;           // 0xD8
	s32 riderTimer;      // 0xDC
	u8 unkE0[0x4];       // 0xE0
	RwV3d riderPos;      // 0xE4
	u8 unkF0[0x8];       // 0xF0
	RwMatrixTag* matrix; // 0xF8
	u8 unkFC[0x8];       // 0xFC
	RwV3d pos;           // 0x104
	u8 unk110[0x4];      // 0x110
	s32 angle;           // 0x114
	u8 unk118[0x4];      // 0x118
	f32 base;            // 0x11C
	f32 range;           // 0x120
	RwV3d scale;         // 0x124
} BreakableWeight;

extern "C" const f32 breakableWeightOne[1];
extern "C" const RwV3d AxisY;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
extern "C" RwMatrixTag* fn_80195B5C(RwMatrixTag* out, const RwMatrixTag* in);

// builds the weight's matrix once: turned about the Y axis by its angle and
// moved to its position at its base height
inline void SetWeightMatrix(BreakableWeight* object)
{
	if (object->matrix == NULL) {
		object->matrix   = new RwMatrixTag;
		RwMatrixTag* out = object->matrix;
		RwMatrixTag matrix;

		fn_80195790(&matrix, &AxisY, breakableWeightOne[0] - fn_800D7AE4(object->angle),
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
extern "C" const f32 breakableWeightHalfDepth[1];
extern "C" const f32 breakableWeightHalfWidth[1];
extern "C" const f32 breakableWeightTopMargin[1];

extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, sAngle* angle);
extern "C" s32 fn_800AB32C(void* task);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

// CheckPlayerTrespassArea (the PS2 build's name): builds the weight's matrix
// and answers whether some player stands under the weight: its position seen
// in the weight's frame no higher than the weight's height above its base
// (plus a margin) and within its scaled half width and half depth. With
// `active`, only the players whose state has bit 0 set count.
inline s32 CheckPlayerTrespassArea(BreakableWeight* object, s32 active)
{
	RwV3d pos;

	SetWeightMatrix(object);
	for (int i = 0; i < 8; i++) {
		if (fn_8003E2E4(i, 0, &pos, NULL) == 0) {
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
		if (pos.y > breakableWeightTopMargin[0] + (object->pos.y - object->base)) {
			continue;
		}
		if ((f32)__fabs(pos.x) > breakableWeightHalfWidth[0] * object->scale.x) {
			continue;
		}
		if ((f32)__fabs(pos.z) > breakableWeightHalfDepth[0] * object->scale.z) {
			continue;
		}
		return 1;
	}
	return 0;
}
