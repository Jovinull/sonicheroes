// Returns whether the word at 0x9B0 is 0.

extern "C" {
struct Obj800892A0 {
	unsigned char pad[0x9b0];
	int f9b0;
};

int fn_800892A0(Obj800892A0* o)
{
	return o->f9b0 == 0 ? 1 : 0;
}
}
