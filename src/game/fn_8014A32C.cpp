// Returns the byte size of the list at arg0 within the table lbl_8042C86C (4 + count * 0x14), or 0 when empty.

extern "C" {
extern int lbl_8042C86C;

int fn_8014A32C(int a)
{
	int t = *(int*)(a + lbl_8042C86C);
	if (t != 0) {
		return t * 0x14 + 4;
	}
	return 0;
}
}
