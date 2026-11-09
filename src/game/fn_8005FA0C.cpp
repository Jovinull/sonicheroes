// Clears lbl_8042C2E8, calls fn_801A4778 with the callback fn_8005FA44 and returns lbl_8042C2E8.

extern "C" {
extern int lbl_8042C2E8;
void fn_8005FA44();
void fn_801A4778(int, void (*)(), int);

int fn_8005FA0C(int a, int b)
{
	lbl_8042C2E8 = 0;
	fn_801A4778(a, fn_8005FA44, b);
	return lbl_8042C2E8;
}
}
