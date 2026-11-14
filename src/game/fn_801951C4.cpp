// Returns the determinant of the matrix's 3x3 rotation part as the triple product
// (up x at) . right (HYPOTHESIS: _rwMatrixDeterminant).
#include "game/rw_engine.h"

extern "C" {
f32 fn_801951C4(const RwMatrix* m)
{
	RwV3d c;
	c.x = m->up.y * m->at.z - m->up.z * m->at.y;
	c.y = m->up.z * m->at.x - m->up.x * m->at.z;
	c.z = m->up.x * m->at.y - m->up.y * m->at.x;
	return c.x * m->right.x + c.y * m->right.y + c.z * m->right.z;
}
}
