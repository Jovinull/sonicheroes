// Advances the cached slot index (lbl_802AD060, kind 0x23B9) and returns the next entry of the
// object whose shape (the halfword its pointer at 0x04 points to) is 6 or 7, stopping at an unused
// entry (byte 1 == -1). See fn_8002128C.
struct G80020E00 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E80020E00 {
	unsigned char f0;
	signed char f1;
	unsigned char pad2[2];
	unsigned short* shape;
};

extern "C" {
extern G80020E00 lbl_802AD060;

E80020E00* fn_80020E00(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x23B9) {
		lbl_802AD060.f4 = 0x23B9;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	int n           = lbl_802AD060.f8 + 1;
	lbl_802AD060.f8 = n;
	if (n > 8) {
		lbl_802AD060.f8 = 8;
	}
	int i          = lbl_802AD060.f8;
	int idx        = i;
	E80020E00* p   = (E80020E00*)(a + i * 8 + 0x14);
	E80020E00* end = (E80020E00*)(a + 0x54);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			break;
		}
		int kind = *p->shape;
		if (kind == 6 || kind == 7) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
