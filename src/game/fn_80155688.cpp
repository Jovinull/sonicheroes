// Decrements the reference count at word 4 of lbl_8042C900 and, at zero, destroys the free list in lbl_8042BD10 (if any); returns the argument.

extern "C" {
struct Count80155688 {
	int a;
	int f4;
};
extern Count80155688 lbl_8042C900;
extern unsigned lbl_8042BD10;
void RwFreeListDestroy(unsigned);

int fn_80155688(int a)
{
	int t           = lbl_8042C900.f4 - 1;
	lbl_8042C900.f4 = t;
	if (t == 0 && lbl_8042BD10 != 0) {
		RwFreeListDestroy(lbl_8042BD10);
		lbl_8042BD10 = 0;
	}
	return a;
}
}
