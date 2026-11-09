// Increments the halfword at lbl_8042C9A4 + lbl_8042C900.

extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042C900;

void fn_80156118(void)
{
	*(short*)(lbl_8042C9A4 + lbl_8042C900) = *(short*)(lbl_8042C9A4 + lbl_8042C900) + 1;
}
}
