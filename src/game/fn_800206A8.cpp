// Returns the object (0x04) of the next entry found through the slot cache lbl_802AD060 (kind
// 0x2552) whose halfword 0x02 has flag 1, provided the collision object's halfword 0x08 has
// flag 8; an unused entry (byte 1 == -1) ends the search. See fn_8002128C.
struct G800206A8 {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E800206A8 {
	signed char f0;
	signed char f1;
	unsigned short flags;
	void* obj;
};

extern "C" {
extern G800206A8 lbl_802AD060;

static inline E800206A8* FindEntry800206A8(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x2552) {
		lbl_802AD060.f4 = 0x2552;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	int n           = lbl_802AD060.f8 + 1;
	lbl_802AD060.f8 = n;
	if (n > 8) {
		lbl_802AD060.f8 = 8;
	}
	int idx = lbl_802AD060.f8;
	if (!(*(unsigned short*)(a + 8) & 8)) {
		return 0;
	}
	E800206A8* p;
	E800206A8* end;
	end = (E800206A8*)(a + 0x54);
	p   = (E800206A8*)(a + idx * 8 + 0x14);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			return 0;
		}
		if ((p->flags & 1) && p->obj != 0) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}

void* fn_800206A8(unsigned int a)
{
	E800206A8* e = FindEntry800206A8(a);
	if (e != 0) {
		return e->obj;
	}
	return 0;
}
}
