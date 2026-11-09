// Clears bit 0 of the halfword at 0xA4; returns 1.

extern "C" {
struct Obj8005FE60 {
	unsigned char pad[0xa4];
	unsigned short fa4;
};

int fn_8005FE60(Obj8005FE60* o)
{
	o->fa4 &= ~1;
	return 1;
}
}
