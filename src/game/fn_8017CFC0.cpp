// Stores three words at +0x1A8, +0x1AC, +0x1B0.

extern "C" {
struct Obj8017CFC0 {
	unsigned char pad[0x1a8];
	int fa8;
	int fac;
	int fb0;
};

void fn_8017CFC0(Obj8017CFC0* o, int a, int b, int c)
{
	o->fa8 = a;
	o->fac = b;
	o->fb0 = c;
}
}
