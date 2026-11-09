// Releases the free list held in slot lbl_8042C958.f0 of the pool table lbl_8042C9A4 (if any) and drops the reference count at +4; returns arg0.

extern "C" {
struct Pool801952E8 {
	int f0;
	int f4;
};
extern int lbl_8042C9A4;
extern Pool801952E8 lbl_8042C958;
void RwFreeListDestroy(int);

int fn_801952E8(int a)
{
	if (*(unsigned*)(lbl_8042C9A4 + lbl_8042C958.f0) != 0) {
		RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C958.f0));
		*(int*)(lbl_8042C9A4 + lbl_8042C958.f0) = 0;
	}
	lbl_8042C958.f4 = lbl_8042C958.f4 - 1;
	return a;
}
}
