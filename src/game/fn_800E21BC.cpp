// Returns 0 right away when the object is flagged 0x4000; otherwise bumps the entry's counter and returns 1 while it is below its limit and the flag of its table row (or of the fallback row) is set.
struct A800E21BC {
	unsigned char pad0[6];
	short f6;
};
struct B800E21BC {
	signed char f0;
	unsigned char pad1[0x11];
	short f12;
	unsigned char pad14[0xB4];
	int fC8;
	unsigned char padCC[0x190];
	signed char f25C;
};
struct E800E21BC {
	unsigned char pad0[9];
	signed char f9;
	unsigned char padA[6];
};

extern "C" {
extern int lbl_802AD070[];
extern E800E21BC lbl_802B0310[];
extern int lbl_80303DC8[];
int fn_800892A0(int a);
E800E21BC* fn_8009262C(int a, int b);

int fn_800E21BC(A800E21BC* a, B800E21BC* b)
{
	short t;
	if ((a->f6 & 0x4000) != 0) {
		return 0;
	}
	t = b->f12;
	b->f12++;

	if (t < b->fC8) {
		if (fn_800892A0(lbl_802AD070[b->f0]) != 0) {
			if ((lbl_802B0310[b->f0].f9 & 1) != 0) {
				return 1;
			}
			goto end;
		}
		if ((fn_8009262C(lbl_80303DC8[b->f25C], 5)->f9 & 1) != 0) {
			return 1;
		}
	}
end:
	return 0;
}
}
