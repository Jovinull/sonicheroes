// Clears every non-zero entry of the eight-slot table lbl_80253A34.

extern "C" {
extern unsigned lbl_80253A34[8];

void fn_800B7B30(void)
{
	int i;
	unsigned* p = lbl_80253A34;
	for (i = 0; i < 8; i++) {
		if (*p != 0) {
			*p = 0;
		}
		p++;
	}
}
}
