// Releases the two free lists held in slot lbl_8042C928.f0 of the pool table lbl_8042C9A4, drops the reference count at +4 and returns the argument.

struct Pool8015A224 {
	int f0;
	int f4;
};

extern "C" {
extern int lbl_8042C9A4;
extern Pool8015A224 lbl_8042C928;
void RwFreeListDestroy(int);

int fn_8015A224(int a)
{
	if (((unsigned*)(lbl_8042C9A4 + lbl_8042C928.f0))[1] != 0) {
		RwFreeListDestroy(((int*)(lbl_8042C9A4 + lbl_8042C928.f0))[1]);
		((int*)(lbl_8042C9A4 + lbl_8042C928.f0))[1] = 0;
	}
	if (*(unsigned*)(lbl_8042C9A4 + lbl_8042C928.f0) != 0) {
		RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C928.f0));
		*(int*)(lbl_8042C9A4 + lbl_8042C928.f0) = 0;
	}
	lbl_8042C928.f4--;
	return a;
}
}
