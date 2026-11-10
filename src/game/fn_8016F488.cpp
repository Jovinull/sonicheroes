// Pushes a copy of the current top 0x40-byte matrix onto the stack in lbl_803EC968 (allocating the slot when needed) while the depth is below 0x1F; returns whether it pushed.
struct Blob8016F488 {
	unsigned char b[0x40];
};
struct Rec8016F488 {
	unsigned char pad0[0x230];
	Blob8016F488* f230[1];
	Blob8016F488* f234[0x20];
	int count;
};

extern "C" {
extern Rec8016F488 lbl_803EC968;
Blob8016F488* fn_80196470();

unsigned int fn_8016F488()
{
	Rec8016F488* g  = &lbl_803EC968;
	int c           = g->count;
	unsigned int ok = (c < 0x1F) ? 1 : 0;
	Blob8016F488** st;
	if (ok != 0) {
		int n    = c + 1;
		st       = g->f234;
		g->count = n;
		if (st[n] == 0) {
			st[g->count] = fn_80196470();
		}
		{
			int i             = g->count;
			Blob8016F488* src = lbl_803EC968.f230[i];
			Blob8016F488* dst = st[i];
			*dst              = *src;
		}
	}
	return ok;
}
}
