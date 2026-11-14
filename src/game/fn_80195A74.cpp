// Rotates the matrix by angle degrees about axis (HYPOTHESIS: RwMatrixRotate): the axis is
// normalized with fn_80199248 (reciprocal square root of its squared length) and the rotation is
// built by fn_80195790 from 1 - cos and sin of the angle, combined as combineOp. Returns the
// matrix.
#include "game/rw_engine.h"

extern "C" {
double sin(double x);
double cos(double x);
// .sdata2 constants of the matrix code (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F6A0; // degrees to radians
extern f32 lbl_8042F694; // 1.0f
// HYPOTHESIS: rwInvSqrt and the axis/angle rotation core (_rwMatrixRotateOneMinusCosineSine).
f32 fn_80199248(f32 value);
RwMatrix* fn_80195790(
    RwMatrix* matrix, const RwV3d* unitAxis, f32 oneMinusCosine, f32 sine, s32 combineOp);

RwMatrix* fn_80195A74(RwMatrix* matrix, const RwV3d* axis, f32 angle, s32 combineOp)
{
	f32 sine;
	f32 radians = lbl_8042F6A0 * angle;
	f32 recip   = fn_80199248(axis->x * axis->x + axis->y * axis->y + axis->z * axis->z);
	RwV3d unitAxis;
	f32 cosine;
	unitAxis.x = axis->x * recip;
	unitAxis.y = axis->y * recip;
	unitAxis.z = axis->z * recip;
	sine       = (f32)sin(radians);
	cosine     = (f32)cos(radians);
	fn_80195790(matrix, &unitAxis, lbl_8042F694 - cosine, sine, combineOp);
	return matrix;
}
}
