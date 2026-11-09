// Releases the free list held in slot lbl_8042C910.f0 of the pool table lbl_8042C9A4, runs fn_8015BF7C and drops the reference count at +4; returns arg0.

extern "C" {
struct Pool801590B8 {
	int f0;
	int f4;
};
extern int lbl_8042C9A4;
extern Pool801590B8 lbl_8042C910;
void RwFreeListDestroy(int);
void fn_8015BF7C(void);

int fn_801590B8(int a)
{
	if (*(unsigned*)(lbl_8042C9A4 + lbl_8042C910.f0) != 0) {
		RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C910.f0));
		*(int*)(lbl_8042C9A4 + lbl_8042C910.f0) = 0;
	}
	fn_8015BF7C();
	lbl_8042C910.f4 = lbl_8042C910.f4 - 1;
	return a;
}
}
