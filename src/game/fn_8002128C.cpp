// Advances the cached slot index and returns the next valid entry, if any.
struct G8002128C {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};
struct E8002128C {
	unsigned char f0;
	signed char f1;
	unsigned char pad[6];
};

extern "C" {
extern G8002128C lbl_802AD060;

E8002128C* fn_8002128C(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x2320) {
		lbl_802AD060.f4 = 0x2320;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	int n           = lbl_802AD060.f8 + 1;
	lbl_802AD060.f8 = n;
	if (n > 8) {
		lbl_802AD060.f8 = 8;
	}
	int idx        = lbl_802AD060.f8;
	E8002128C* p   = (E8002128C*)(a + idx * 8 + 0x14);
	E8002128C* end = (E8002128C*)(a + 0x54);
	while (p < end) {
		if (p->f1 != -1) {
			lbl_802AD060.f8 = idx;
			return p;
		}
		break;
	}
	return 0;
}
}
