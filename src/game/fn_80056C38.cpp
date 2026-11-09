// Returns whether flag 0x10000 of the word at 0x18 is set.

extern "C" {
struct Obj80056C38 {
	unsigned char pad[0x18];
	unsigned f18;
};

int fn_80056C38(Obj80056C38* o)
{
	return (o->f18 & 0x10000) != 0;
}
}
