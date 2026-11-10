// Returns ids 7..10 unchanged; otherwise looks the id up in the six-entry table lbl_80241C98 and returns the value of lbl_80241CD8 selected by that slot's byte (0 when unknown).
struct Ent800419BC {
	unsigned char pad0[0x25C];
	signed char f25C;
};

extern "C" {
extern int lbl_80241C98[];
extern Ent800419BC* lbl_802AD0D0[];
extern int lbl_80241CD8[];

static inline int FindIndex800419BC(int a)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (a == lbl_80241C98[i]) {
			return i;
		}
	}
	return -1;
}

int fn_800419BC(int a)
{
	int idx;
	Ent800419BC* e;
	switch (a) {
		case 7:
		case 8:
		case 9:
		case 10:
			return a;
	}
	idx = FindIndex800419BC(a);
	e   = lbl_802AD0D0[idx];
	if (idx == -1 || e == 0) {
		return 0;
	}
	return lbl_80241CD8[e->f25C];
}
}
