// Sets flag 0x10000000 of the word at 4.

extern "C" {
struct Obj80064380 {
	unsigned char pad[4];
	unsigned f4;
};

void fn_80064380(Obj80064380* o)
{
	o->f4 |= 0x10000000;
}
}
