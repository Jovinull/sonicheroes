// Returns the orthogonality error of the matrix's rotation part: the sum of the squared dot
// products of each axis pair taken cyclically (up.at, at.right, right.up)
// (HYPOTHESIS: _rwMatrixOrthogonalError).
#include "game/rw_engine.h"

static inline f32 RwV3dDot(const RwV3d* a, const RwV3d* b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

extern "C" {
f32 fn_80195210(const RwMatrix* m)
{
	f32 d0 = RwV3dDot(&m->up, &m->at);
	f32 d1 = RwV3dDot(&m->at, &m->right);
	f32 d2 = RwV3dDot(&m->right, &m->up);
	return d0 * d0 + d1 * d1 + d2 * d2;
}
}
