// Clears the word at arg0 within the table lbl_8042C85C.

extern "C" {
extern int lbl_8042C85C;

void fn_801489BC(int a)
{
	*(int*)(a + lbl_8042C85C) = 0;
}
}
