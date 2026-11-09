// Clears the word at arg0 within the table lbl_8042C860.

extern "C" {
extern int lbl_8042C860;

void fn_80148AC4(int a)
{
	*(int*)(a + lbl_8042C860) = 0;
}
}
