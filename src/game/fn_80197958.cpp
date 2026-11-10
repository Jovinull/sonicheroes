// Frees the shared list when allocated, drops the reference count and returns the argument.
struct G {
	int f0;
	int f4;
};

extern "C" {
extern G lbl_8042C978;
extern int lbl_8042C9A4;
void RwFreeListDestroy(unsigned int p);

int fn_80197958(int a)
{
	unsigned int v = *(unsigned int*)(lbl_8042C9A4 + lbl_8042C978.f0);
	if (v != 0) {
		RwFreeListDestroy(v);
	}
	lbl_8042C978.f4--;
	return a;
}
}
