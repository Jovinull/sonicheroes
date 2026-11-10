// Maps a character id to its slot number: ids 7..10 map to 0..3, otherwise the id is looked up in the six-entry table lbl_80241C98 and the slot's selector byte is returned (-1 when unknown).
struct Ent800418A8 {
	unsigned char pad0[0x25C];
	signed char f25C;
};

extern "C" {
extern int lbl_80241C98[];
extern Ent800418A8* lbl_802AD0D0[];

static inline int FindIndex800418A8(int a)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (a == lbl_80241C98[i]) {
			return i;
		}
	}
	return -1;
}

int fn_800418A8(int a)
{
	int idx;
	Ent800418A8* e;
	switch (a) {
		case 7:
			return 0;
		case 8:
			return 1;
		case 9:
			return 2;
		case 10:
			return 3;
		default:
			idx = FindIndex800418A8(a);
			e   = lbl_802AD0D0[idx];
			if (idx != -1 && e != 0) {
				return e->f25C;
			}
			return -1;
	}
}
}
