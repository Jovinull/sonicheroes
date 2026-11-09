// Sets bit 3 of the halfword at 0x206.

extern "C" {
struct Obj80091278 {
	unsigned char pad[0x206];
	short s206;
};

void fn_80091278(Obj80091278* o)
{
	o->s206 |= 8;
}
}
