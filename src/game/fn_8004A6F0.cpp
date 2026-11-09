// Registers the callback fn_8004A67C for the handle and remembers the cell (c, d); lbl_8042C1E0 points at its 0x10-byte record inside the 0x420-byte row, or is cleared when there is no handle.

extern "C" {
extern int lbl_8042C1D8;
extern int lbl_8042C1DC;
extern int lbl_8042C1E0;
void fn_80159900(unsigned, void (*)());
void fn_8004A67C();

void fn_8004A6F0(int a, unsigned b, int c, int d)
{
	if (b == 0) {
		lbl_8042C1E0 = 0;
		return;
	}
	fn_80159900(b, fn_8004A67C);
	lbl_8042C1D8 = c;
	lbl_8042C1DC = d;
	lbl_8042C1E0 = a + c * 0x420 + d * 0x10 + 0xb38;
}
}
