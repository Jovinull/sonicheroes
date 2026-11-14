// Combines two rotation-translation keys (HYPOTHESIS: an RtQuat-style product on the quaternion
// at 0x8 with the translations at 0x18 added): out.real = a.real * b.real - a.imag . b.imag,
// out.imag = a.imag x b.imag + b.imag * a.real + a.imag * b.real, out.t = a.t + b.t. Field names
// are inferred from this function only.
#include "types.h"

struct Vec8013E3D0 {
	f32 x;
	f32 y;
	f32 z;
};

struct Key8013E3D0 {
	u8 pad0[0x8];
	Vec8013E3D0 imag;        // 0x8
	f32 real;                // 0x14
	Vec8013E3D0 translation; // 0x18
};

extern "C" {
void fn_8013E3D0(Key8013E3D0* out, const Key8013E3D0* a, const Key8013E3D0* b)
{
	out->real = a->real * b->real
	    - (a->imag.x * b->imag.x + a->imag.y * b->imag.y + a->imag.z * b->imag.z);
	out->imag.x = a->imag.y * b->imag.z - a->imag.z * b->imag.y;
	out->imag.y = a->imag.z * b->imag.x - a->imag.x * b->imag.z;
	out->imag.z = a->imag.x * b->imag.y - a->imag.y * b->imag.x;
	out->imag.x += b->imag.x * a->real;
	out->imag.y += b->imag.y * a->real;
	out->imag.z += b->imag.z * a->real;
	out->imag.x += a->imag.x * b->real;
	out->imag.y += a->imag.y * b->real;
	out->imag.z += a->imag.z * b->real;
	out->translation.x = a->translation.x + b->translation.x;
	out->translation.y = a->translation.y + b->translation.y;
	out->translation.z = a->translation.z + b->translation.z;
}
}
