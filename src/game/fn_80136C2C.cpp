// Stores four floats into the record at +0x2C..+0x38.
struct Rec80136C2C {
	unsigned char pad0[0x2C];
	float f2C;
	float f30;
	float f34;
	float f38;
};

extern "C" void fn_80136C2C(Rec80136C2C* r, float a, float b, float c, float d)
{
	r->f2C = a;
	r->f30 = b;
	r->f34 = c;
	r->f38 = d;
}
