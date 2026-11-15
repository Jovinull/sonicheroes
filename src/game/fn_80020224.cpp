// Places `dst` relative to `src` through an offset (position at +0x0, angles x/y/z at +0xC..+0x14):
// the vector from the offset position to src's position (+0x8) is rotated by the offset angles
// (Z, then X, then Y) on the matrix stack and added back to the offset position as dst's position,
// and dst's angles (+0x24) are src's plus the offset's. The first argument is unused. HYPOTHESIS:
// attaching an object to a moving parent; the roles are UNKNOWN.
#include "game/matrix.h"

struct Offset80020224 {
	RwV3d position; // 0x0
	s32 angleX;     // 0xC
	s32 angleY;     // 0x10
	s32 angleZ;     // 0x14
};

struct Placement80020224 {
	u8 pad0[8];
	RwV3d position; // 0x8
	u8 pad14[0x24 - 0x14];
	s32 angleX; // 0x24
	s32 angleY; // 0x28
	s32 angleZ; // 0x2C
};

extern "C" void fn_80020224(
    void* unused, Placement80020224* dst, Placement80020224* src, Offset80020224* offset)
{
	RwV3d r;
	RwV3d d;

	PushUnitMatrix();
	d.x = src->position.x - offset->position.x;
	d.y = src->position.y - offset->position.y;
	d.z = src->position.z - offset->position.z;
	RotateZ(pCurrentMatrix, offset->angleZ);
	RotateX(pCurrentMatrix, offset->angleX);
	RotateY(pCurrentMatrix, offset->angleY);
	CalcPoint(pCurrentMatrix, &d, &r);
	dst->position.x = r.x + offset->position.x;
	dst->position.y = r.y + offset->position.y;
	dst->position.z = r.z + offset->position.z;
	PopMatrixEx();
	dst->angleX = src->angleX + offset->angleX;
	dst->angleY = src->angleY + offset->angleY;
	dst->angleZ = src->angleZ + offset->angleZ;
}
