// Pushes a copy of the given 0x40-byte matrix onto the stack in lbl_803EC968 while the depth is below 0x1F and clears the two follow-up fields; returns whether it pushed.
struct Blob8016F728 {
	unsigned char b[0x40];
};
struct Rec8016F728 {
	unsigned char pad0[0x230];
	Blob8016F728* f230[1];
	Blob8016F728* f234[0x20];
	int count;
	unsigned char pad2B8[0xD0];
	int f388;
	unsigned char pad38C[0x10];
	int f39C;
};

extern "C" {
extern Rec8016F728 lbl_803EC968;
Blob8016F728* fn_80196470();

unsigned int fn_8016F728(Blob8016F728* p)
{
	Rec8016F728* g  = &lbl_803EC968;
	int c           = g->count;
	unsigned int ok = (c < 0x1F) ? 1 : 0;
	Blob8016F728** st;
	if (ok != 0) {
		int n    = c + 1;
		st       = g->f234;
		g->count = n;
		if (st[n] == 0) {
			st[g->count] = fn_80196470();
		}
		{
			Blob8016F728* dst = st[g->count];
			*dst              = *p;
		}
	}
	lbl_803EC968.f388 = 0;
	lbl_803EC968.f39C = 0;
	return ok;
}
}
