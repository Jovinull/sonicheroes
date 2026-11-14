// Advances the cached slot index (lbl_802AD060, kind 0x2510) and returns the next entry for id
// (byte 0) whose object (0x04) has value as byte 0 of the 0x30-byte record selected by the
// entry's byte 1, stopping at an unused entry (byte 1 == -1). See fn_8002128C and fn_80020330.
struct G800207C4 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct Obj800207C4 {
	unsigned char pad0[0x10];
	unsigned char* records; // 0x10: 0x30-byte records
};

struct E800207C4 {
	signed char f0;
	signed char f1;
	unsigned char pad2[2];
	Obj800207C4* obj;
};

extern "C" {
extern G800207C4 lbl_802AD060;

E800207C4* fn_800207C4(unsigned int a, int id, unsigned char value)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x2510) {
		lbl_802AD060.f4 = 0x2510;
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
	E800207C4* p   = (E800207C4*)(a + i * 8 + 0x14);
	E800207C4* end = (E800207C4*)(a + 0x54);
	for (; p < end; p++, idx++) {
		int k = p->f1;
		if (k == -1) {
			break;
		}
		if (p->f0 == id && p->obj != 0 && p->obj->records[k * 0x30] == value) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
