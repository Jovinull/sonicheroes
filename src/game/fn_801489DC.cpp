// Sets the word at arg0 within the table lbl_8042C85C when the word at arg1 is non-zero.

extern "C" {
extern int lbl_8042C85C;

void fn_801489DC(int a, int b)
{
	if (*(int*)(b + lbl_8042C85C) != 0) {
		*(int*)(a + lbl_8042C85C) = 1;
	}
}
}
