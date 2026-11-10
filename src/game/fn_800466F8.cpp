// In modes 0x36/0x37 switches to mode 0x38 when the speed exceeds the scaled limit; returns the new mode or 0.
struct Rec800466F8 {
	unsigned char padC[0xC];
	float fC;
};
struct Lst800466F8 {
	unsigned char pad0[0x20];
	Rec800466F8** f20;
};
struct Pl800466F8 {
	unsigned char pad0[0x8AE];
	short f8AE;
	unsigned char pad8B0[0x10];
	float f8C0;
	unsigned char pad8C4[0x20];
	Lst800466F8* f8E4;
};

extern "C" {
extern float lbl_8042D1EC;
extern float lbl_8042D254;

int fn_800466F8(Pl800466F8* p)
{
	short m = p->f8AE;
	if (m != 0x36 && m != 0x37) {
		return 0;
	}
	if (p->f8C0 > lbl_8042D1EC * (lbl_8042D254 * (*p->f8E4->f20)->fC)) {
		p->f8AE = 0x38;
	} else {
		return 0;
	}
	return 0x38;
}
}
