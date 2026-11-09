// Walks consecutive pairs of the list lbl_8042C7A0 (count at +4), fetching each pair with fn_8014D208 and handing it to fn_8005FC74.

extern "C" {
struct List80133B50 {
	void* f0;
	int f4;
};
extern List80133B50* lbl_8042C7A0;
void fn_8014D208(void*, int, void*);
void fn_8005FC74(void*, void*);

void fn_80133B50(void)
{
	unsigned char a[12];
	unsigned char b[12];
	int i;
	for (i = 0; i < lbl_8042C7A0->f4 - 1; i++) {
		fn_8014D208(lbl_8042C7A0->f0, i, a);
		fn_8014D208(lbl_8042C7A0->f0, i + 1, b);
		fn_8005FC74(a, b);
	}
}
}
