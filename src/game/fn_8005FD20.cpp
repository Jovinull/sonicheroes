// Sets bit 3 of the halfword at 0xA4.

extern "C" {
struct Obj8005FD20 {
	unsigned char pad[0xa4];
	unsigned short fa4;
};

void fn_8005FD20(Obj8005FD20* o)
{
	o->fa4 |= 8;
}
}
