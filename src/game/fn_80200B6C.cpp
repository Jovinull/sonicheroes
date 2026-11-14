// Passes o and the linear value o->f8 + t * o->f4 to fn_80200D84; returns o. The unit is built
// with -fp_contract off: retail keeps the multiply and add separate.
struct Obj80200B6C {
	unsigned char pad0[0x4];
	float f4;
	float f8;
};
extern "C" {
void fn_80200D84(Obj80200B6C* o, float v);
Obj80200B6C* fn_80200B6C(Obj80200B6C* o, float t)
{
	fn_80200D84(o, o->f8 + t * o->f4);
	return o;
}
}
