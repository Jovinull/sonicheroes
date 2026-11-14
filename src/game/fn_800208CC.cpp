// Advances the cached slot index (lbl_802AD060, kind 0x24CE) and returns the next entry for id
// (byte 0) whose shape (the halfword its pointer at 0x04 points to) is 6 or 7, stopping at an unused
// entry (byte 1 == -1). See fn_8002128C.
struct G800208CC {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E800208CC {
	signed char f0;
	signed char f1;
	unsigned char pad2[2];
	unsigned short* shape;
};

extern "C" {
extern G800208CC lbl_802AD060;

E800208CC* fn_800208CC(unsigned int a, int id)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x24CE) {
		lbl_802AD060.f4 = 0x24CE;
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
	E800208CC* p   = (E800208CC*)(a + i * 8 + 0x14);
	E800208CC* end = (E800208CC*)(a + 0x54);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			break;
		}
		if (p->f0 == id) {
			int kind = *p->shape;
			if (kind == 6 || kind == 7) {
				lbl_802AD060.f8 = idx;
				return p;
			}
		}
	}
	return 0;
}
}
