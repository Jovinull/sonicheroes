// Clears the word at arg0 within the table lbl_8042CF48.

extern "C" {
extern int lbl_8042CF48;

void fn_801FC3C8(int a)
{
	*(int*)(a + lbl_8042CF48) = 0;
}
}
