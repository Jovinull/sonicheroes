// Returns whether flag 2 of the word at 0x18 is set.

extern "C" {
struct Obj80056C50 {
	unsigned char pad[0x18];
	unsigned f18;
};

int fn_80056C50(Obj80056C50* o)
{
	return (o->f18 & 2) != 0;
}
}
