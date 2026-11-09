// Clears lbl_8042CA40; returns 1.

extern "C" {
extern int lbl_8042CA40;

int fn_801ACC5C(void)
{
	lbl_8042CA40 = 0;
	return 1;
}
}
