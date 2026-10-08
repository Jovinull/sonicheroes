#include "game/calc.h"

// calc.cpp: C++ file/function identities corroborated by PS2 DWARF.
// The GameCube unit boundary is inferred from the correlated function sequence.
// Seven bodies match directly. GetRotYXZ retains ten f30/f31 register fields
// across ten instructions; tools/fix_calc_registers.py bounds that permutation.
// Local declarations, expression lifetimes, helper expansion and compiler
// choices have not reproduced the allocation. See docs/calc-register-evidence.md.
// Remove the normalizer when a source spelling reproduces these fields.
struct RwV3d {
	f32 x, y, z;
};
struct RwMatrixTag {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};
extern "C" {
f64 atan2(f64, f64);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
}
extern const __declspec(section ".sdata2") f32 lbl_8042DFB8;

void GetRotXYZ(RwMatrixTag* mat, s32* ax, s32* ay, s32* az)
{
	f32 s, c;
	s32 aay, aaz;
	aaz = (10430.381f * (f32)atan2(mat->right.y, mat->right.x));
	*az = aaz;
	s   = fn_800D7B00(aaz);
	c   = fn_800D7AE4(aaz);
	if (!((aaz + 0x2000) & 0x4000)) {
		aay = (10430.381f * (f32)atan2(-mat->right.z * c, mat->right.x));
		if (c < lbl_8042DFB8)
			aay += 0x8000;
	} else {
		aay = (10430.381f * (f32)atan2(-mat->right.z * s, mat->right.y));
		if (s < lbl_8042DFB8)
			aay += 0x8000;
	}
	*ay = (s16)aay;
	*ax = (10430.381f * (f32)atan2(mat->at.x * s - mat->at.y * c, mat->up.y * c - mat->up.x * s));
}

void GetRotYXZ(RwMatrixTag* mat, s32* ax, s32* ay, s32* az)
{
	f32 s, c;
	s32 aax, aaz;
	aaz = (10430.381f * (f32)atan2(-mat->up.x, mat->up.y));
	*az = aaz;
	s   = fn_800D7B00(aaz);
	c   = fn_800D7AE4(aaz);
	if (!((aaz + 0x2000) & 0x4000)) {
		aax = (10430.381f * (f32)atan2(mat->up.z * c, mat->up.y));
		if (c < lbl_8042DFB8)
			aax += 0x8000;
	} else {
		aax = (10430.381f * (f32)atan2(mat->up.z * s, -mat->up.x));
		if (s < lbl_8042DFB8)
			aax += 0x8000;
	}
	*ax = (s16)aax;
	*ay = (10430.381f
	    * (f32)atan2(mat->at.x * c + mat->at.y * s, mat->right.x * c + mat->right.y * s));
}

void GetRotZXY(RwMatrixTag* mat, s32* ax, s32* ay, s32* az)
{
	f32 s, c;
	s32 aax, aay;
	aay = (10430.381f * (f32)atan2(mat->at.x, mat->at.z));
	*ay = aay;
	s   = fn_800D7B00(aay);
	c   = fn_800D7AE4(aay);
	if (!((aay + 0x2000) & 0x4000)) {
		aax = (10430.381f * (f32)atan2(-mat->at.y * c, mat->at.z));
		if (c < lbl_8042DFB8)
			aax += 0x8000;
	} else {
		aax = (10430.381f * (f32)atan2(-mat->at.y * s, mat->at.x));
		if (s < lbl_8042DFB8)
			aax += 0x8000;
	}
	*ax = (s16)aax;
	*az = (10430.381f
	    * (f32)atan2(mat->up.z * s - mat->up.x * c, mat->right.x * c - mat->right.z * s));
}

void GetAngleXY(f32 dx, f32 dy, f32 dz, s32* ax, s32* ay)
{
	s32 aax, aay;
	f32 c;
	aay = (10430.381f * (f32)atan2(dx, dz));
	*ay = aay;
	if (!((aay + 0x2000) & 0x4000)) {
		c   = fn_800D7AE4(aay);
		aax = (10430.381f * (f32)atan2(-dy * c, dz));
	} else {
		c   = fn_800D7B00(aay);
		aax = (10430.381f * (f32)atan2(-dy * c, dx));
	}
	if (c < lbl_8042DFB8)
		aax = (s16)(aax + 0x8000);
	*ax = aax;
}

void GetAngleXZ(f32 dx, f32 dy, f32 dz, s32* ax, s32* az)
{
	s32 aax, aaz;
	f32 c;
	aaz = (10430.381f * (f32)atan2(-dx, dy));
	*az = aaz;
	if (!((aaz + 0x2000) & 0x4000)) {
		c   = fn_800D7AE4(aaz);
		aax = (10430.381f * (f32)atan2(dz * c, dy));
	} else {
		c   = fn_800D7B00(aaz);
		aax = (10430.381f * (f32)atan2(dz * c, -dx));
	}
	if (c < lbl_8042DFB8)
		aax = (s16)(aax + 0x8000);
	*ax = aax;
}

void GetAngleYZ(f32 dx, f32 dy, f32 dz, s32* ay, s32* az)
{
	s32 aay, aaz;
	f32 c;
	aaz = (10430.381f * (f32)atan2(dy, dx));
	*az = aaz;
	if (!((aaz + 0x2000) & 0x4000)) {
		c   = fn_800D7AE4(aaz);
		aay = (10430.381f * (f32)atan2(-dz * c, dx));
	} else {
		c   = fn_800D7B00(aaz);
		aay = (10430.381f * (f32)atan2(-dz * c, dy));
	}
	if (c < lbl_8042DFB8)
		aay = (s16)(aay + 0x8000);
	*ay = aay;
}

s32 InterDivAngF(s32 a1, s32 a2, f32 d1, f32 d2)
{
	s32 a2r = (a2 - a1) & 0xffff;
	if (a2r <= 0x7fff)
		return a1 + (a2r * d1) / (d1 + d2);
	return a1 + (-((0x10000 - a2r) * d1)) / (d1 + d2);
}

f32 InterDivPosF(f32 p1, f32 p2, f32 d1, f32 d2)
{
	return (p1 * d2 + p2 * d1) / (d1 + d2);
}

const __declspec(section ".sdata2") f32 lbl_8042DFB8 = 0.0f;
