// Trivial accessor.

extern "C" {
struct S6 {
	unsigned char pad[0x8a];
	unsigned short s8a;
	unsigned short s8c;
};

unsigned short fn_80158918(S6* o)
{
	return o->s8a;
}
}
