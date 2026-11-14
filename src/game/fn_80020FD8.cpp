// Advances the cached slot index (lbl_802AD060, kind 0x237B) and returns the next entry of the
// object whose shape (the halfword its pointer at 0x04 points to) is 2 or 3, stopping at an unused
// entry (byte 1 == -1). See fn_8002128C.
struct G80020FD8 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E80020FD8 {
	unsigned char f0;
	signed char f1;
	unsigned char pad2[2];
	unsigned short* shape;
};

extern "C" {
extern G80020FD8 lbl_802AD060;

E80020FD8* fn_80020FD8(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x237B) {
		lbl_802AD060.f4 = 0x237B;
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
	E80020FD8* p   = (E80020FD8*)(a + i * 8 + 0x14);
	E80020FD8* end = (E80020FD8*)(a + 0x54);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			break;
		}
		int kind = *p->shape;
		if (kind == 2 || kind == 3) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
