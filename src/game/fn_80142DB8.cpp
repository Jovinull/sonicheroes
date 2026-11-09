// Tears down the three globals lbl_8042C830/34/38 (releasing each non-null one), then returns 1.

extern "C" {
extern unsigned lbl_8042C830;
extern unsigned lbl_8042C834;
extern unsigned lbl_8042C838;
void fn_8015C834(void*);
void fn_801B3A10(void*);

int fn_80142DB8(void)
{
	if (lbl_8042C830 != 0) {
		fn_8015C834((void*)lbl_8042C830);
		lbl_8042C830 = 0;
	}
	if (lbl_8042C834 != 0) {
		fn_801B3A10((void*)lbl_8042C834);
		lbl_8042C834 = 0;
	}
	if (lbl_8042C838 != 0) {
		fn_801B3A10((void*)lbl_8042C838);
		lbl_8042C838 = 0;
	}
	return 1;
}
}
