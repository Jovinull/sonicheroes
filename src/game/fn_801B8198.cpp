// Copies the word at *arg1 into lbl_8042CA90; returns 1.

extern "C" {
extern int lbl_8042CA90;

int fn_801B8198(int unused, int* p)
{
	lbl_8042CA90 = *p;
	return 1;
}
}
