// Trivial accessor.

extern "C" {
struct P14 {
	int f0;
	int f4;
	int f8;
	int fc;
};
struct S7 {
	unsigned char pad[0x14];
	P14* f14;
};

void fn_8015C388(S7* o, int a)
{
	o->f14->fc = a;
}
}
