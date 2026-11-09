// Raises the halfword at 0x202 to the given value when it is not above it, and sets the high bit of the halfword at 0x206.

extern "C" {
struct Obj8009128C {
	unsigned char pad[0x202];
	short s202;
	unsigned char pad1[2];
	short s206;
};

void fn_8009128C(Obj8009128C* o, int v)
{
	if (o->s202 <= v) {
		o->s202 = v;
		o->s206 |= 0x8000;
	}
}
}
