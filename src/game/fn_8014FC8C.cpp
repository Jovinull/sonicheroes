// Destroys the two free lists of the entry and releases the entry.
struct G8014FC8C {
	int f0;
	int f4;
};

extern "C" {
extern G8014FC8C lbl_8042C8D8;
extern char* lbl_8042C9A4;
void RwFreeListDestroy(int a);
void fn_80196BCC(int a, void* b, int c, char* d);
void fn_8014EFE8();
void fn_8014F008();

int fn_8014FC8C(int a)
{
	fn_80196BCC(((int*)(lbl_8042C9A4 + lbl_8042C8D8.f0))[1], (void*)fn_8014EFE8, 0, lbl_8042C9A4);
	fn_80196BCC(*(int*)(lbl_8042C9A4 + lbl_8042C8D8.f0), (void*)fn_8014F008, 0, lbl_8042C9A4);
	RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C8D8.f0));
	RwFreeListDestroy(((int*)(lbl_8042C9A4 + lbl_8042C8D8.f0))[1]);
	*(int*)(lbl_8042C9A4 + lbl_8042C8D8.f0)     = 0;
	((int*)(lbl_8042C9A4 + lbl_8042C8D8.f0))[1] = 0;
	lbl_8042C8D8.f4--;
	return a;
}
}
