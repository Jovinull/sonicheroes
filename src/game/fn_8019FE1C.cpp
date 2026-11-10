// Accessor for the indexed manager table entry.
extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042C9B0;
int fn_8019FE1C()
{
	return ((int*)(lbl_8042C9A4 + lbl_8042C9B0))[4 / 4];
}
}
