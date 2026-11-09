// Reads the 4-byte value into lbl_8042C8BC and, when arg1 is 8, a second one into lbl_8042C8B8; returns arg0, or 0 if a read fails.

extern "C" {
unsigned fn_80193884(void*, void*, int);
extern unsigned char lbl_8042C8BC[4];
extern unsigned char lbl_8042C8B8[4];

void* fn_8014DB78(void* a, int k)
{
	if (fn_80193884(a, lbl_8042C8BC, 4) == 0) {
		return 0;
	}
	if (k == 8 && fn_80193884(a, lbl_8042C8B8, 4) == 0) {
		return 0;
	}
	return a;
}
}
