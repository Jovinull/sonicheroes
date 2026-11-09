// Clears the word at arg0 within the table lbl_8042C858.

extern "C" {
extern int lbl_8042C858;

void fn_80147A38(int a)
{
	*(int*)(a + lbl_8042C858) = 0;
}
}
