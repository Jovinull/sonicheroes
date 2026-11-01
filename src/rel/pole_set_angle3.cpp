#include "types.h"

// TObjPole::SetAngle3FromNormal (the PS2 build's name), the same in the
// thirteen stage modules that share the engine core: the angles that stand a
// pole along a surface normal. Normals close to an axis snap to it (and are
// made exact); otherwise the pitch comes from the normal's Z, the roll from
// its X over Y, and the yaw is the angle, about the normal, between the base's
// up axis turned by those two and the normal turned a quarter about its cross
// with the Y axis (flipped to point down), or the pole's own turn when the
// normal is nearly Y. The 1.0 is the unit's own literal, which the module's
// other pole code reads as poleOne (tools/fix_stage11_symbols.py names it and
// makes it global).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct Pole {
	u8 unk000[0xCC];
	s32 angY; // 0x0CC
	u8 unk0D0[0x28];
	f32 turn; // 0x0F8
} Pole;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 poleZero[1];
extern "C" const RwV3d poleBaseUp;
extern "C" const f32 poleMinusOne;
extern "C" const f32 poleRadToAngle;
extern "C" const f32 poleTurnToAngle;
extern "C" const f32 poleUpLimit;
extern "C" const f32 poleUpNear;
extern "C" const f32 poleSideNarrow;
extern "C" const f32 poleDownLimit;
extern "C" const f32 poleDownNear;
extern "C" const f32 poleFrontLimit;
extern "C" const f32 poleBackLimit;
extern "C" const f32 poleCrossMin;

extern "C" double asin(double x);
extern "C" double atan2(double y, double x);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
extern "C" f32 fn_801991B4(const RwV3d* v);
extern "C" void fn_801990E0(RwV3d* out, const RwV3d* in);
s32 VectorAngle(RwV3d* a, RwV3d* b, RwV3d* normal);

extern "C" void SetAngle3FromNormal__8TObjPoleCFP5RwV3dP6sAngle(
    const Pole* pole, RwV3d* normal, sAngle* ang)
{
	RwMatrixTag matrix;
	RwMatrixTag turn;

	if (normal->z > poleUpLimit
	    || (normal->z > poleUpNear && (f32)__fabs(normal->y) < poleSideNarrow)) {
		ang->x    = 0x4000;
		ang->y    = 0;
		ang->z    = 0;
		normal->x = poleZero[0];
		normal->y = poleZero[0];
		normal->z = 1.0f;
		return;
	}
	if (normal->z < poleDownLimit
	    || (normal->z < poleDownNear && (f32)__fabs(normal->y) < poleSideNarrow)) {
		ang->x    = 0xC000;
		ang->y    = 0x8000;
		ang->z    = 0;
		normal->x = poleZero[0];
		normal->y = poleZero[0];
		normal->z = poleMinusOne;
		return;
	}
	if (normal->y > poleFrontLimit) {
		ang->x    = 0;
		ang->y    = 0;
		ang->z    = 0;
		normal->x = poleZero[0];
		normal->y = 1.0f;
		normal->z = poleZero[0];
		return;
	}
	if (normal->y < poleBackLimit) {
		ang->x    = 0x8000;
		ang->y    = 0;
		ang->z    = 0;
		normal->x = poleZero[0];
		normal->y = poleMinusOne;
		normal->z = poleZero[0];
		return;
	}
	ang->x = (s32)(poleRadToAngle * (f32)asin(normal->z));
	ang->z = -(s32)(poleRadToAngle * (f32)atan2(normal->x, normal->y));
	fn_80195790(&matrix, &AxisX, 1.0f - fn_800D7AE4(ang->x), fn_800D7B00(ang->x), 0);
	fn_80195790(&matrix, &AxisZ, 1.0f - fn_800D7AE4(ang->z), fn_800D7B00(ang->z), 2);
	RwV3d up = poleBaseUp;
	RwV3d side;
	RwV3d dir;

	fn_8019947C(&up, &up, 1, &matrix);
	side.x = AxisY.y * normal->z - AxisY.z * normal->y;
	side.y = AxisY.z * normal->x - AxisY.x * normal->z;
	side.z = AxisY.x * normal->y - AxisY.y * normal->x;
	if (fn_801991B4(&side) > poleCrossMin) {
		fn_801990E0(&side, &side);
		fn_80195790(&turn, &side, 1.0f, 1.0f, 0);
		fn_8019947C(&dir, normal, 1, &turn);
		{
			f32 y = dir.y;

			if (y > poleZero[0]) {
				dir.x = poleMinusOne * dir.x;
				dir.y = poleMinusOne * y;
				dir.z = poleMinusOne * dir.z;
			}
		}
		ang->y = VectorAngle(&up, &dir, normal);
	} else {
		{
			s32 add = (s32)(poleTurnToAngle * pole->turn);

			ang->y = add + pole->angY;
		}
	}
}
