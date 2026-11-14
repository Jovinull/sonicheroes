// Advances the cached slot index (lbl_802AD060, kind 0x244A) and returns the next entry for id
// (byte 0) whose shape (the halfword its pointer at 0x04 points to) is 0, stopping at an unused
// entry (byte 1 == -1). See fn_8002128C.
struct G800209C8 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E800209C8 {
	signed char f0;
	signed char f1;
	unsigned char pad2[2];
	unsigned short* shape;
};

extern "C" {
extern G800209C8 lbl_802AD060;

E800209C8* fn_800209C8(unsigned int a, int id)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x244A) {
		lbl_802AD060.f4 = 0x244A;
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
	E800209C8* p   = (E800209C8*)(a + i * 8 + 0x14);
	E800209C8* end = (E800209C8*)(a + 0x54);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			break;
		}
		if (p->f0 == id) {
			int kind = *p->shape;
			if (kind == 0) {
				lbl_802AD060.f8 = idx;
				return p;
			}
		}
	}
	return 0;
}
}
