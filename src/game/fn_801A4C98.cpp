// Accessor for the indexed manager table entry.
extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042C9C4;
int fn_801A4C98()
{
	return ((int*)(lbl_8042C9A4 + lbl_8042C9C4))[0x10 / 4];
}
}
