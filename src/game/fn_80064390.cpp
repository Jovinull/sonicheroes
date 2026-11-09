// When bit 16 of the flags word at 4 is set, ORs the value into the word the pointer at 0x2C points to (if any).

extern "C" {
struct Obj80064390 {
	unsigned char pad[4];
	int f4;
	unsigned char pad1[0x2c - 8];
	int* p2c;
};

void fn_80064390(Obj80064390* o, int v)
{
	if ((o->f4 & 0x10000) != 0) {
		int* p = o->p2c;
		if (p != 0) {
			*p |= v;
		}
	}
}
}
