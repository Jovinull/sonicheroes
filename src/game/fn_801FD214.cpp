// Returns the pointer stored at arg0 within lbl_8042CF48 plus 0x98.

extern "C" {
extern int lbl_8042CF48;

int fn_801FD214(int a)
{
	return *(int*)(a + lbl_8042CF48) + 0x98;
}
}
