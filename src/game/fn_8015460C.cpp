// Like fn_8014DB78 but with the pair lbl_8042C8F4 / lbl_8042C8F0.

extern "C" {
unsigned fn_80193884(void*, void*, int);
extern unsigned char lbl_8042C8F4[4];
extern unsigned char lbl_8042C8F0[4];

void* fn_8015460C(void* a, int k)
{
	if (fn_80193884(a, lbl_8042C8F4, 4) == 0) {
		return 0;
	}
	if (k == 8 && fn_80193884(a, lbl_8042C8F0, 4) == 0) {
		return 0;
	}
	return a;
}
}
