// Trivial accessor.

extern "C" {
struct S8 {
	signed char c0;
	signed char c1;
	unsigned char pad[0xa];
	signed char cc;
	signed char cd;
};

void fn_8015C6F8(S8* o, signed char a, signed char b)
{
	o->c0 = a;
	o->cc = b;
}
}
