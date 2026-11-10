// Initialises the effect from the global camera record: copies its vectors and word and clears the first four words.
struct Src80131348 {
	unsigned char pad0[0x1B8];
	float f1B8;
	float f1BC;
	float f1C0;
	float f1C4;
	float f1C8;
	float f1CC;
	unsigned char pad1D0[0x14];
	int f1E4;
};
struct Dst80131348 {
	int f0;
	int f4;
	int f8;
	int fC;
	float f10;
	float f14;
	float f18;
	unsigned char pad1C[8];
	int f24;
	unsigned char pad28[0xC];
	float f34;
	float f38;
	float f3C;
};

extern "C" {
extern Src80131348* lbl_8042C248;

void fn_80131348(Dst80131348* d)
{
	Src80131348* s = lbl_8042C248;
	d->f10         = s->f1B8;
	d->f14         = s->f1BC;
	d->f18         = s->f1C0;
	d->f34         = s->f1C4;
	d->f38         = s->f1C8;
	d->f3C         = s->f1CC;
	d->f24         = s->f1E4;
	d->f0          = 0;
	d->f4          = 0;
	d->f8          = 0;
	d->fC          = 0;
}
}
