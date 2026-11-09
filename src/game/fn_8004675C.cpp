// Trivial accessor.

extern "C" {
struct S2 {
	unsigned char pad[0x8ae];
	short s8ae;
};

void fn_8004675C(S2* o)
{
	o->s8ae = 0x36;
}
}
