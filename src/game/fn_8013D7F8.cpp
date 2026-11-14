// Builds a matrix from a rotation-translation key (HYPOTHESIS: RtQuatUnitConvertToMatrix on the
// unit quaternion at 0x8, followed by the translation at 0x18 as position). The .sdata2 constants
// lbl_8042F1B4, lbl_8042F1B0 and lbl_8042F1B8 are 2.0f, 1.0f and 0.0f (HYPOTHESIS); the matrix
// is flagged orthonormal (3).
// NonMatching: same instructions in the same order, but the floating-point registers of the
// quaternion components and products are numbered differently (20 words).
#include "game/rw_engine.h"

struct Vec8013D7F8 {
	f32 x;
	f32 y;
	f32 z;
};

struct Key8013D7F8 {
	u8 pad0[0x8];
	Vec8013D7F8 imag;        // 0x8
	f32 real;                // 0x14
	Vec8013D7F8 translation; // 0x18
};

extern "C" {
extern f32 lbl_8042F1B0;
extern f32 lbl_8042F1B4;
extern f32 lbl_8042F1B8;

void fn_8013D7F8(RwMatrix* matrix, const Key8013D7F8* key)
{
	f32 y = key->imag.y;
	f32 z = key->imag.z;
	f32 w = key->real;
	f32 x = key->imag.x;

	matrix->right.x = lbl_8042F1B0 - lbl_8042F1B4 * (y * y + z * z);
	matrix->right.y = lbl_8042F1B4 * (x * y + w * z);
	matrix->right.z = lbl_8042F1B4 * (z * x - w * y);
	matrix->up.x    = lbl_8042F1B4 * (x * y - w * z);
	matrix->up.y    = lbl_8042F1B0 - lbl_8042F1B4 * (z * z + x * x);
	matrix->up.z    = lbl_8042F1B4 * (y * z + w * x);
	matrix->at.x    = lbl_8042F1B4 * (z * x + w * y);
	matrix->at.y    = lbl_8042F1B4 * (y * z - w * x);
	matrix->at.z    = lbl_8042F1B0 - lbl_8042F1B4 * (x * x + y * y);
	matrix->pos.x   = lbl_8042F1B8;
	matrix->pos.y   = lbl_8042F1B8;
	matrix->pos.z   = lbl_8042F1B8;
	matrix->flags   = 3;
	matrix->pos.x   = key->translation.x;
	matrix->pos.y   = key->translation.y;
	matrix->pos.z   = key->translation.z;
}
}
