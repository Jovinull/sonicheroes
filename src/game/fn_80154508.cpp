// Runs fn_80196BCC over the free list in slot lbl_8042C8E8.f0 of lbl_8042C9A4 (callback fn_80153E7C), destroys and clears it, and drops the reference count at +4; returns arg0.

extern "C" {
struct Pool80154508 {
	int f0;
	int f4;
};
extern int lbl_8042C9A4;
extern Pool80154508 lbl_8042C8E8;
extern unsigned char fn_80153E7C[];
void RwFreeListDestroy(int);
void fn_80196BCC(int, void*, int, int);

int fn_80154508(int a)
{
	fn_80196BCC(*(int*)(lbl_8042C9A4 + lbl_8042C8E8.f0), fn_80153E7C, 0, lbl_8042C9A4);
	RwFreeListDestroy(*(int*)(lbl_8042C9A4 + lbl_8042C8E8.f0));
	*(int*)(lbl_8042C9A4 + lbl_8042C8E8.f0) = 0;
	lbl_8042C8E8.f4--;
	return a;
}
}
