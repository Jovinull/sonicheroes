// If flag 0x10000 of the word at 4 is set and a target pointer is held at 0x2C, stores v through it.

extern "C" {
struct Obj800643C0 {
	unsigned char pad[4];
	int f4;
	unsigned char pad1[0x2c - 8];
	int* p2c;
};

void fn_800643C0(Obj800643C0* o, int v)
{
	if ((o->f4 & 0x10000) != 0) {
		int* t = o->p2c;
		if (t != 0) {
			*t = v;
		}
	}
}
}
