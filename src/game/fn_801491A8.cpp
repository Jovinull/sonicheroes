// Marks the owner's word at lbl_8042C85C as set once fn_80142E20 succeeds; returns the owner, or
// 0 when the word was clear and fn_80142E20 failed.
extern "C" {
extern int lbl_8042C85C;
void* fn_80142E20(void);

int fn_801491A8(int owner)
{
	int off = lbl_8042C85C;
	if (*(int*)(owner + off) == 0) {
		if (fn_80142E20() == 0) {
			return 0;
		}
		*(int*)(owner + off) = 1;
	}
	return owner;
}
}
