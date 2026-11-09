// Destroys the free list held at word 4 of lbl_8042C828 and clears it; returns the argument.

extern "C" {
struct Holder8013E688 {
	int a;
	unsigned f4;
};
extern Holder8013E688 lbl_8042C828;
void RwFreeListDestroy(unsigned);

int fn_8013E688(int a)
{
	if (lbl_8042C828.f4 != 0) {
		RwFreeListDestroy(lbl_8042C828.f4);
		lbl_8042C828.f4 = 0;
	}
	return a;
}
}
