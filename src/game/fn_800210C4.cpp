// Advances the cached slot index (lbl_802AD060, kind 0x235C) and returns the next entry of the
// object whose shape (the halfword its pointer at 0x04 points to) is 1, stopping at an unused
// entry (byte 1 == -1). See fn_8002128C.
struct G800210C4 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E800210C4 {
	unsigned char f0;
	signed char f1;
	unsigned char pad2[2];
	unsigned short* shape;
};

extern "C" {
extern G800210C4 lbl_802AD060;

E800210C4* fn_800210C4(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x235C) {
		lbl_802AD060.f4 = 0x235C;
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
	E800210C4* p   = (E800210C4*)(a + i * 8 + 0x14);
	E800210C4* end = (E800210C4*)(a + 0x54);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			break;
		}
		int kind = *p->shape;
		if (kind == 1) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
