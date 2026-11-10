// Initialises the record from the owner's data block and the selected position table entry (copies vectors, an id and two not-zero flags).
struct Src80130DF0 {
	unsigned char pad0[0x38];
	float f38;
	float f3C;
	float f40;
	unsigned char pad44[8];
	int f4C;
	unsigned char pad50[0x28];
	int f78;
};
struct Own80130DF0 {
	unsigned char pad0[0x10];
	Src80130DF0* f10;
};
struct Pos80130DF0 {
	unsigned char pad0[0x40];
	float f40;
	float f44;
	float f48;
};
struct Dst80130DF0 {
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
extern Pos80130DF0* lbl_80303DC8[];
extern int lbl_8042C1FC;

void fn_80130DF0(Dst80130DF0* d, Own80130DF0* o)
{
	Src80130DF0* s = o->f10;
	Pos80130DF0* p;
	int k  = lbl_8042C1FC;
	d->f0  = 0;
	d->f4  = 0;
	d->f10 = s->f38;
	d->f14 = s->f3C;
	d->f18 = s->f40;
	p      = lbl_80303DC8[k];
	d->f34 = p->f40;
	d->f38 = p->f44;
	d->f3C = p->f48;
	d->f24 = s->f4C;
	d->f8  = (unsigned int)__cntlzw(s->f78) >> 5;
	d->fC  = (unsigned int)__cntlzw(s->f78) >> 5;
}
}
