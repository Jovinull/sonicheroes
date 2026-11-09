// Fills in the block size parameters and returns the table.
struct Obj801781AC {
	int f0;
	int f4;
	int f8;
	int fC;
	int f10;
	int f14;
	int f18;
};

extern "C" {
extern char lbl_8023BC38[];

void* fn_801781AC(Obj801781AC* o, int* out)
{
	int q;
	int r;
	int v;
	o->f0 = 8;
	v     = 0x10;
	o->f4 = 0xE;
	o->f8 = *(volatile int*)&o->f0 + 1;
	o->fC = *(volatile int*)&o->f4 + 1;
	do {
		v += v;
		q = v / o->f8;
		r = (q + 0x5A) / q;
	} while (v < r * o->fC);
	o->f10 = 0x5B;
	o->f14 = q;
	o->f18 = r;
	*out   = v;
	return lbl_8023BC38;
}
}
