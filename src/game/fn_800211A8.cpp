// Advances the cached slot index (lbl_802AD060, kind 0x233E) and returns the next entry of the
// object whose shape (the halfword its pointer at 0x04 points to) is 0, stopping at an unused
// entry (byte 1 == -1). See fn_8002128C.
struct G800211A8 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E800211A8 {
	unsigned char f0;
	signed char f1;
	unsigned char pad2[2];
	unsigned short* shape;
};

extern "C" {
extern G800211A8 lbl_802AD060;

E800211A8* fn_800211A8(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x233E) {
		lbl_802AD060.f4 = 0x233E;
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
	E800211A8* p   = (E800211A8*)(a + i * 8 + 0x14);
	E800211A8* end = (E800211A8*)(a + 0x54);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			break;
		}
		int kind = *p->shape;
		if (kind == 0) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
