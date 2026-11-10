// Accessor for the indexed manager table entry.
extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042C9C4;
int fn_801A4574(int a)
{
	((int*)(lbl_8042C9A4 + lbl_8042C9C4))[0x20 / 4] = a;
	return 1;
}
}
