// Trivial accessor.

extern "C" {
struct S11 {
	unsigned char pad[0xc];
	unsigned fc;
};

int fn_80201390(S11* o)
{
	return (o->fc >> 1) & 1;
}
}
