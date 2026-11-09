// Trivial accessor.

extern "C" {
extern int lbl_8042CA58;

int fn_801B15F0(int u, int a)
{
	lbl_8042CA58 = a;
	return 1;
}
}
