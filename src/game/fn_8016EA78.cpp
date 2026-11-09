// Trivial accessor.

extern "C" {
struct S9 {
	unsigned char pad[0x10];
	unsigned f10;
};

int fn_8016EA78(S9* o)
{
	return (o->f10 >> 1) & 1;
}
}
