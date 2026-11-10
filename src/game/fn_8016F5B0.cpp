// Pushes a matrix onto the stack in lbl_803EC968 while the depth is below 0x1F, either as a copy of the current top (arg 0) or through fn_80195674 using the given source, and clears the two follow-up fields; returns whether it pushed.
struct Blob8016F5B0 {
	unsigned char b[0x40];
};
struct Rec8016F5B0 {
	unsigned char pad0[0x230];
	Blob8016F5B0* f230[1];
	Blob8016F5B0* f234[0x20];
	int count;
	unsigned char pad2B8[0xD0];
	int f388;
	unsigned char pad38C[0x10];
	int f39C;
};

extern "C" {
extern Rec8016F5B0 lbl_803EC968;
Blob8016F5B0* fn_80196470();
void fn_80195674(Blob8016F5B0* d, unsigned int a, Blob8016F5B0* s);

unsigned int fn_8016F5B0(unsigned int a)
{
	Rec8016F5B0* g  = &lbl_803EC968;
	int c           = g->count;
	unsigned int ok = (c < 0x1F) ? 1 : 0;
	Blob8016F5B0** st;
	if (ok != 0) {
		int n    = c + 1;
		st       = g->f234;
		g->count = n;
		if (st[n] == 0) {
			st[g->count] = fn_80196470();
		}
		if (a == 0) {
			int i             = g->count;
			Blob8016F5B0* src = lbl_803EC968.f230[i];
			Blob8016F5B0* dst = st[i];
			*dst              = *src;
		} else {
			int i = g->count;
			fn_80195674(st[i], a, lbl_803EC968.f230[i]);
		}
	}
	lbl_803EC968.f388 = 0;
	lbl_803EC968.f39C = 0;
	return ok;
}
}
