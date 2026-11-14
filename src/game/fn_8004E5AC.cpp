// Walks the players of the current team record down from n - 1 and returns the first index whose
// word 0x90 is nonzero; index 0 is returned untested, and -1 when n is 0.
extern "C" {
struct Player8004E5AC {
	unsigned char pad[0x90];
	int f90;
	unsigned char pad1[0x114 - 0x94];
};
struct Team8004E5AC {
	Player8004E5AC pl[8];
	unsigned char pad[0x2324 - 8 * 0x114];
};
extern Team8004E5AC lbl_802B908C[];
extern int lbl_8042C1FC;
int fn_8004E5AC(int unused, int n)
{
	int i = n - 1;
	if (i < 0) {
		return -1;
	}
	for (; i != 0; i--) {
		if (lbl_802B908C[lbl_8042C1FC].pl[i].f90 != 0) {
			return i;
		}
	}
	return i;
}
}
