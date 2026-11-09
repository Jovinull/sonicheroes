// Releases the free list held in slot lbl_8042C8F8.f0 of the pool table lbl_8042C9A4 (if any) and drops the reference count at +4; returns arg0.

extern "C" {
struct Pool801547FC {
	int f0;
	int f4;
};
extern int lbl_8042C9A4;
extern Pool801547FC lbl_8042C8F8;
void RwFreeListDestroy(int);

int fn_801547FC(int a)
{
	if (*(unsigned*)(lbl_8042C9A4 + lbl_8042C8F8.f0) != 0) {
		RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C8F8.f0));
		*(int*)(lbl_8042C9A4 + lbl_8042C8F8.f0) = 0;
	}
	lbl_8042C8F8.f4 = lbl_8042C8F8.f4 - 1;
	return a;
}
}
