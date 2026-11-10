// Initialises the effect from the owner's record: clears two words, copies its vectors and word and clears the other two.
struct Src8013139C {
	unsigned char pad0[0x38];
	float f38;
	float f3C;
	float f40;
	unsigned char pad44[8];
	int f4C;
	float f50;
	float f54;
	float f58;
};
struct Dst8013139C {
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
struct Own8013139C {
	unsigned char pad0[0x10];
	Src8013139C* f10;
};

extern "C" {
void fn_8013139C(Dst8013139C* d, Own8013139C* o)
{
	Src8013139C* s = o->f10;
	d->f0          = 0;
	d->f4          = 0;
	d->f10         = s->f38;
	d->f14         = s->f3C;
	d->f18         = s->f40;
	d->f34         = s->f50;
	d->f38         = s->f54;
	d->f3C         = s->f58;
	d->f24         = s->f4C;
	d->f8          = 0;
	d->fC          = 0;
}
}
