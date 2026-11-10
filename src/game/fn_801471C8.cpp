// Stores the value into the third slot of the pool table entry.
extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042BCE0;
void fn_801471C8(int v)
{
	((int*)(lbl_8042C9A4 + lbl_8042BCE0))[2] = v;
}
}
