// Loads the GX position (and optionally normal) matrix 0 for drawing (HYPOTHESIS: the RenderWare
// GameCube driver's matrix setup): the view matrix lbl_803EDB8C, multiplied first by the given
// world matrix when there is one (fn_80195674, HYPOTHESIS: RwMatrixMultiply), is transposed into a
// GX 3x4 matrix with the x and z rows negated, then made the current matrix.
#include "dolphin/gx/GXTransform.h"
#include "game/rw_engine.h"

extern "C" {
// View matrix of the current camera (HYPOTHESIS).
extern RwMatrix lbl_803EDB8C;

RwMatrix* fn_80195674(RwMatrix* out, const RwMatrix* a, const RwMatrix* b);

void fn_801AD0AC(const RwMatrix* world, s32 loadNormal)
{
	RwMatrix combined;
	const RwMatrix* m;
	f32 gx[3][4];

	if (world) {
		combined.flags = 0x20003;
		fn_80195674(&combined, world, &lbl_803EDB8C);
		m = &combined;
	} else {
		m = &lbl_803EDB8C;
	}

	gx[0][0] = -m->right.x;
	gx[0][1] = -m->up.x;
	gx[0][2] = -m->at.x;
	gx[0][3] = -m->pos.x;
	gx[1][0] = m->right.y;
	gx[1][1] = m->up.y;
	gx[1][2] = m->at.y;
	gx[1][3] = m->pos.y;
	gx[2][0] = -m->right.z;
	gx[2][1] = -m->up.z;
	gx[2][2] = -m->at.z;
	gx[2][3] = -m->pos.z;
	GXLoadPosMtxImm(gx, 0);
	if (loadNormal) {
		GXLoadNrmMtxImm(gx, 0);
	}
	GXSetCurrentMtx(0);
}
}
