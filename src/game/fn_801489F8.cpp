// Reads the word at the given offset of the table lbl_8042C85C points to and passes it, with size 4, to fn_80193474.

extern "C" {
extern int lbl_8042C85C;
void fn_80193474(int, int*, int);

void fn_801489F8(int a, int unused, int index)
{
	int v = *(int*)(index + lbl_8042C85C);
	fn_80193474(a, &v, 4);
}
}
