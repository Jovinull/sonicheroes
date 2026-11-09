// Releases the free list held in slot lbl_8042C9A8.f0 of the pool table lbl_8042C9A4 (if any) and drops the reference count at +4; returns arg0.

extern "C" {
struct Pool8019DF78 {
	int f0;
	int f4;
};
extern int lbl_8042C9A4;
extern Pool8019DF78 lbl_8042C9A8;
void RwFreeListDestroy(int);

int fn_8019DF78(int a)
{
	if (*(unsigned*)(lbl_8042C9A4 + lbl_8042C9A8.f0) != 0) {
		RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C9A8.f0));
		*(int*)(lbl_8042C9A4 + lbl_8042C9A8.f0) = 0;
	}
	lbl_8042C9A8.f4 = lbl_8042C9A8.f4 - 1;
	return a;
}
}
