// Copies the 0x50-byte record field by field (the bytes at 0x2C and 0x40 as single bytes).

extern "C" {
struct Rec800BA754 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int f28;
	unsigned char c2c;
	unsigned char pad[3];
	int f30;
	int f34;
	int f38;
	int f3c;
	unsigned char c40;
	unsigned char pad1[3];
	int f44;
	int f48;
	int f4c;
};

void fn_800BA754(Rec800BA754* d, Rec800BA754* s)
{
	d->f0  = s->f0;
	d->f4  = s->f4;
	d->f8  = s->f8;
	d->fc  = s->fc;
	d->f10 = s->f10;
	d->f14 = s->f14;
	d->f18 = s->f18;
	d->f1c = s->f1c;
	d->f20 = s->f20;
	d->f24 = s->f24;
	d->f28 = s->f28;
	d->c2c = s->c2c;
	d->f30 = s->f30;
	d->f34 = s->f34;
	d->f38 = s->f38;
	d->f3c = s->f3c;
	d->c40 = s->c40;
	d->f44 = s->f44;
	d->f48 = s->f48;
	d->f4c = s->f4c;
}
}
