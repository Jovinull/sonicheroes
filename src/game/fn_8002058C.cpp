// Returns the object (0x04) of the next entry found through the slot cache lbl_802AD060 (kind
// 0x259C) whose halfword 0x02 has flag 2, provided the collision object's halfword 0x08 has
// flag 2; an unused entry (byte 1 == -1) ends the search. See fn_8002128C.
struct G8002058C {
	unsigned int f0;
	int f4;
	int f8;
	int fC;
};

struct E8002058C {
	signed char f0;
	signed char f1;
	unsigned short flags;
	void* obj;
};

extern "C" {
extern G8002058C lbl_802AD060;

static inline E8002058C* FindEntry8002058C(unsigned int a)
{
	if (lbl_802AD060.f0 != a) {
		lbl_802AD060.f0 = a;
		lbl_802AD060.f4 = -1;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	if (lbl_802AD060.f4 != 0x259C) {
		lbl_802AD060.f4 = 0x259C;
		lbl_802AD060.fC = -1;
		lbl_802AD060.f8 = -1;
	}
	int n           = lbl_802AD060.f8 + 1;
	lbl_802AD060.f8 = n;
	if (n > 8) {
		lbl_802AD060.f8 = 8;
	}
	int idx = lbl_802AD060.f8;
	if (!(*(unsigned short*)(a + 8) & 2)) {
		return 0;
	}
	E8002058C* p;
	E8002058C* end;
	end = (E8002058C*)(a + 0x54);
	p   = (E8002058C*)(a + idx * 8 + 0x14);
	for (; p < end; p++, idx++) {
		if (p->f1 == -1) {
			return 0;
		}
		if ((p->flags & 2) && p->obj != 0) {
			lbl_802AD060.f8 = idx;
			return p;
		}
	}
	return 0;
}

void* fn_8002058C(unsigned int a)
{
	E8002058C* e = FindEntry8002058C(a);
	if (e != 0) {
		return e->obj;
	}
	return 0;
}
}
