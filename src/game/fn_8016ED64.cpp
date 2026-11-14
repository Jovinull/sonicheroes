// Returns the cached squared length at 0x398 of the global block lbl_803EC968, computing it on
// first use (HYPOTHESIS): after fn_8016F964, scales the ratio of the floats at 0x2B8 and 0x2C0 by
// those at 0x390 and 0x394, transforms the vector (that value, 0, 0) by the matrix at 0x308
// (fn_8019947C, HYPOTHESIS: RwV3dTransformVectors) and stores its squared length, flagging the
// cache at 0x39C as valid. Field names are inferred from this function only.
// NonMatching: the retail code stores x before loading the 0.0f constant for y and z; ours
// schedules that load first (12 words differ; same pattern as fn_80173668).
#include "game/rw_engine.h"

struct Block8016ED64 {
	u8 pad0[0x2B8];
	f32 value2B8; // 0x2B8
	u8 pad2BC[0x4];
	f32 value2C0; // 0x2C0
	u8 pad2C4[0x308 - 0x2C4];
	RwMatrix matrix; // 0x308
	u8 pad348[0x390 - 0x348];
	f32 value390;      // 0x390
	f32 value394;      // 0x394
	f32 lengthSquared; // 0x398
	s32 valid;         // 0x39C
};

extern "C" {
extern Block8016ED64 lbl_803EC968;
extern f32 lbl_8042F464;

void fn_8016F964(void);
RwV3d* fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrix* matrix);

f32 fn_8016ED64(void)
{
	if (!lbl_803EC968.valid) {
		RwV3d v;

		fn_8016F964();
		v.x = lbl_803EC968.value394
		    * (lbl_803EC968.value390 * (lbl_803EC968.value2B8 / lbl_803EC968.value2C0));
		v.y = lbl_8042F464;
		v.z = lbl_8042F464;
		fn_8019947C(&v, &v, 1, &lbl_803EC968.matrix);
		lbl_803EC968.valid         = 1;
		lbl_803EC968.lengthSquared = v.x * v.x + v.y * v.y + v.z * v.z;
	}
	return lbl_803EC968.lengthSquared;
}
}
