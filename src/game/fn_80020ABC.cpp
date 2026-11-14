// Advances the cached slot index (lbl_802AD060, kind 0x241F) and, when bit 0 of the halfword at
// 0x08 of the collision object is set, returns the next entry whose object's record (selected by
// byte 1) has a word 4 sharing a bit with mask; an unused entry (byte 1 == -1) ends the search.
// See fn_8002128C and fn_800207C4.
struct G80020ABC {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct Obj80020ABC {
	unsigned char pad0[0x10];
	unsigned char* records; // 0x10: 0x30-byte records
};

struct E80020ABC {
	signed char f0;
	signed char f1;
	unsigned char pad2[2];
	Obj80020ABC* obj;
};

extern "C" {
extern G80020ABC lbl_802AD060;

E80020ABC* fn_80020ABC(unsigned int a, unsigned int mask)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x241F) {
		lbl_802AD060.f4 = 0x241F;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	int n           = lbl_802AD060.f8 + 1;
	lbl_802AD060.f8 = n;
	if (n > 8) {
		lbl_802AD060.f8 = 8;
	}
	int i   = lbl_802AD060.f8;
	int idx = i;
	if (!(*(unsigned short*)(a + 8) & 1)) {
		return 0;
	}
	E80020ABC* p;
	E80020ABC* end;
	end = (E80020ABC*)(a + 0x54);
	p   = (E80020ABC*)(a + i * 8 + 0x14);
	for (; p < end; p++, idx++) {
		int k          = p->f1;
		Obj80020ABC* o = p->obj;
		if (k == -1) {
			return 0;
		}
		if (o != 0 && (*(unsigned int*)(o->records + k * 0x30 + 4) & mask)) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
