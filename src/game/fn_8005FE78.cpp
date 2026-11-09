// Sets bit 0 of the halfword at 0xA4 unless bit 2 is set; returns whether it did.

extern "C" {
struct Obj8005FE78 {
	unsigned char pad[0xa4];
	unsigned short fa4;
};

int fn_8005FE78(Obj8005FE78* o)
{
	unsigned short t = o->fa4;
	if ((t & 4) != 0) {
		return 0;
	}
	o->fa4 = t | 1;
	return 1;
}
}
