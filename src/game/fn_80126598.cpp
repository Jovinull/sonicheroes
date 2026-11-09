// Returns 2 when the word at 0x14 is 0, otherwise 1.

extern "C" {
struct Obj80126598 {
	unsigned char pad[0x14];
	unsigned f14;
};

int fn_80126598(Obj80126598* o)
{
	if (o->f14 == 0) {
		return 2;
	}
	return 1;
}
}
