// Trivial accessor.

extern "C" {
struct S10 {
	unsigned char pad[8];
	unsigned f8;
};

int fn_801733E8(S10* o)
{
	return o->f8 & 4;
}
}
