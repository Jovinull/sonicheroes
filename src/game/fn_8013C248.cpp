// Clears the word at the object + lbl_8042C818 offset.

extern "C" {
extern int lbl_8042C818;

void fn_8013C248(int a)
{
	*(int*)(a + lbl_8042C818) = 0;
}
}
