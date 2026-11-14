// Looks up a table entry and forwards (id, entry->f1, index) to fn_80137D0C.

struct Entry801379A0 {
	unsigned char pad0[1];
	signed char f1;
};

extern "C" {
extern Entry801379A0* lbl_802AD0D0[];
int fn_80137D0C(int a, int b, int c);

int fn_801379A0(int a, int idx)
{
	Entry801379A0* e = lbl_802AD0D0[idx];
	if (e == 0) {
		return -1;
	}
	return fn_80137D0C(a, e->f1, idx);
}
}
