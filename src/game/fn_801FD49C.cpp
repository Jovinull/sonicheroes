// Releases the object in lbl_8042CF50 with fn_801B3A10 and clears the pointer, if set; returns the argument.

extern "C" {
extern unsigned lbl_8042CF50;
void fn_801B3A10(unsigned);

int fn_801FD49C(int a)
{
	if (lbl_8042CF50 != 0) {
		fn_801B3A10(lbl_8042CF50);
		lbl_8042CF50 = 0;
	}
	return a;
}
}
