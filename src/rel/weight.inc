// TObjWeight (the PS2 build's name), the weight that drops on the players:
// the fields its matrix and area checks read, and SetWeightMatrix, which the
// checks inline.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct Weight {
	u8 unk00[0xDC];      // 0x00
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
