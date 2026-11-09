// Fills entry a (0x14 bytes each) of the table lbl_803EC488: id, then the b, c, d values and e at word 4; returns 1.

extern "C" {
struct Entry80146C2C {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
};
extern Entry80146C2C lbl_803EC488[];

int fn_80146C2C(int a, int b, int c, int d, int e)
{
	Entry80146C2C* t = &lbl_803EC488[a];
	t->f0            = a;
	t->f8            = b;
	t->fc            = c;
	t->f10           = d;
	t->f4            = e;
	return 1;
}
}
