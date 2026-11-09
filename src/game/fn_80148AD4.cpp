// Sets the word at arg0 within the table lbl_8042C860 when the word at arg1 is non-zero.

extern "C" {
extern int lbl_8042C860;

void fn_80148AD4(int a, int b)
{
	if (*(int*)(b + lbl_8042C860) != 0) {
		*(int*)(a + lbl_8042C860) = 1;
	}
}
}
