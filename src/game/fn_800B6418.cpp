// Releases the object held in lbl_8042C388 (fn_800B6450 with 1) and clears the pointer, if any.

extern "C" {
extern void* lbl_8042C388;
void fn_800B6450(void*, int);

void fn_800B6418()
{
	if (lbl_8042C388 != 0) {
		fn_800B6450(lbl_8042C388, 1);
		lbl_8042C388 = 0;
	}
}
}
