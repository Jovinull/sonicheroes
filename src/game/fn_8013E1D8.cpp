// Writes each 0x24-byte entry of the table at +0x10 (count at +4) to stream arg1: the 0x20-byte body, then its entry offset relative to the table; returns 0 on the first failed write, else 1.

extern "C" {
unsigned fn_8019336C(int, void*, int);
unsigned fn_80193474(int, int*, int);
struct Table8013E1D8 {
	unsigned char pad[4];
	int f4;
	unsigned char pad1[8];
	int* f10;
};

int fn_8013E1D8(Table8013E1D8* o, int h)
{
	int sp8;
	int* p;
	int i;
	int* base;
	base = o->f10;
	i    = 0;
	p    = base;
	while (i < o->f4) {
		if (fn_8019336C(h, p + 1, 0x20) == 0) {
			return 0;
		}
		sp8 = *p - (int)base;
		if (fn_80193474(h, &sp8, 4) == 0) {
			return 0;
		}
		p += 9;
		i++;
	}
	return 1;
}
}
