// Resets the state: runs fn_8017C024 with (0x7FFF, -1), releases the block at 0x190/0x194 if present and zeroes the 0x120-byte buffer arg1.

extern "C" {
struct Obj8017C48C {
	unsigned char pad[0x190];
	int f190;
	int f194;
};
void fn_8017C024(void*, void*, int, int);
void fn_8017CE74(void*, int);
void* memset(void*, int, unsigned);

void fn_8017C48C(Obj8017C48C* o, void* b)
{
	fn_8017C024(o, b, 0x7fff, -1);
	if (o->f190 != 0) {
		fn_8017CE74(o, o->f194);
		o->f194 = 0;
		o->f190 = 0;
	}
	memset(b, 0, 0x120);
}
}
