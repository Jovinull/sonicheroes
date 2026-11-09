// Clears flag 0x10000000 of the word at 4.

extern "C" {
struct Obj80064370 {
	unsigned char pad[4];
	unsigned f4;
};

void fn_80064370(Obj80064370* o)
{
	o->f4 &= 0xefffffff;
}
}
