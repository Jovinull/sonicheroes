// Advances the cached slot index (lbl_802AD060, kind 0x23F6; a new value is cached at 0x0C and
// restarts the search) and, when bit 0 of the halfword at
// 0x08 of the collision object is set, returns the next entry whose object's record (selected by
// byte 1) has value as byte 0; an unused entry (byte 1 == -1) ends the search.
// See fn_8002128C and fn_800207C4.
struct G80020BD8 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct Obj80020BD8 {
	unsigned char pad0[0x10];
	unsigned char* records; // 0x10: 0x30-byte records
};

struct E80020BD8 {
	signed char f0;
	signed char f1;
	unsigned char pad2[2];
	Obj80020BD8* obj;
};

extern "C" {
extern G80020BD8 lbl_802AD060;

E80020BD8* fn_80020BD8(unsigned int a, unsigned char value)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x23F6) {
		lbl_802AD060.f4 = 0x23F6;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (value != -1 && lbl_802AD060.fC != value) {
		lbl_802AD060.fC = value;
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
	E80020BD8* p;
	E80020BD8* end;
	end = (E80020BD8*)(a + 0x54);
	p   = (E80020BD8*)(a + i * 8 + 0x14);
	for (; p < end; p++, idx++) {
		int k          = p->f1;
		Obj80020BD8* o = p->obj;
		if (k == -1) {
			return 0;
		}
		if (o != 0 && o->records[k * 0x30] == value) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}
}
