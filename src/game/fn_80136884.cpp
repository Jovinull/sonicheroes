// Marks slot i (flag word at 0x40 + 4 * i) and remembers the slot index at 0x94.

extern "C" {
struct Obj80136884 {
	unsigned char pad[0x40];
	int f40[7];
	unsigned char pad1[0x94 - 0x5c];
	int f94;
};

void fn_80136884(Obj80136884* o, int i)
{
	if (i > 0 || i < 7) {
		o->f40[i] = 1;
		o->f94    = i;
	}
}
}
