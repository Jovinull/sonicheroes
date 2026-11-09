// Like fn_8014DB78 but with the pair lbl_8042C8B4 / lbl_8042C8B0.

extern "C" {
unsigned fn_80193884(void*, void*, int);
extern unsigned char lbl_8042C8B4[4];
extern unsigned char lbl_8042C8B0[4];

void* fn_8014DC98(void* a, int k)
{
	if (fn_80193884(a, lbl_8042C8B4, 4) == 0) {
		return 0;
	}
	if (k == 8 && fn_80193884(a, lbl_8042C8B0, 4) == 0) {
		return 0;
	}
	return a;
}
}
