// Stores six floats at offsets 0x10 to 0x24 of an object.
struct Obj801F4A70 {
	unsigned char pad0[0x10];
	float f[6];
};

extern "C" {
void fn_801F4A70(Obj801F4A70* o, float a, float b, float c, float d, float e, float g)
{
	o->f[0] = a;
	o->f[1] = b;
	o->f[2] = c;
	o->f[3] = d;
	o->f[4] = e;
	o->f[5] = g;
}
}
