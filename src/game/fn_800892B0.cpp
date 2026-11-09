// Returns whether the word at 0x9B0 is non-zero.

extern "C" {
struct Obj800892B0 {
	unsigned char pad[0x9b0];
	int f9b0;
};

int fn_800892B0(Obj800892B0* o)
{
	return o->f9b0 != 0;
}
}
