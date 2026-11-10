// Rotates the vector (lbl_8042DA74, lbl_8042DA74, z) by the given Y angle through a temporary unit matrix and stores it at +0x1D8.
#include "game/matrix.h"

struct Obj800A3CE0 {
	unsigned char pad0[0x1D8];
	RwV3d f1D8;
};

extern float lbl_8042DA74;

extern "C" void fn_800A3CE0(Obj800A3CE0* o, int ang, float z)
{
	RwV3d v;
	v.x = lbl_8042DA74;
	v.y = lbl_8042DA74;
	v.z = z;
	PushUnitMatrix();
	RotateY(0, ang);
	CalcVector(0, &v, &o->f1D8);
	PopMatrixEx();
}
