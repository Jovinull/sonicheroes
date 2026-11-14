// Stores three floats at offsets 0x10, 0x14 and 0x18 of an object.
struct Obj801F4A8C {
	unsigned char pad0[0x10];
	float f10;
	float f14;
	float f18;
};

extern "C" {
void fn_801F4A8C(Obj801F4A8C* o, float a, float b, float c)
{
	o->f10 = a;
	o->f14 = b;
	o->f18 = c;
}
}
