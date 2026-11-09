// Increments the reference count at word 4 of lbl_8042C938 and, on the first reference, initializes lbl_803EC6A0 (fn_8015C728); returns the argument.

extern "C" {
struct Count8015C5E4 {
	int a;
	int f4;
};
extern Count8015C5E4 lbl_8042C938;
extern unsigned char lbl_803EC6A0[];
void fn_8015C728(void*);

int fn_8015C5E4(int a)
{
	int t           = lbl_8042C938.f4 + 1;
	lbl_8042C938.f4 = t;
	if (t == 1) {
		fn_8015C728(lbl_803EC6A0);
	}
	return a;
}
}
