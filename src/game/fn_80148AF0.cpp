// Reads the word at the given offset of the table lbl_8042C860 points to and passes it, with size 4, to fn_80193474.

extern "C" {
extern int lbl_8042C860;
void fn_80193474(int, int*, int);

void fn_80148AF0(int a, int unused, int index)
{
	int v = *(int*)(index + lbl_8042C860);
	fn_80193474(a, &v, 4);
}
}
