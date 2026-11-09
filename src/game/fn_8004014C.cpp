// Deletes the two objects held in lbl_8042C1B0 and lbl_8042C1B4 and clears the pointers.

extern "C" {
extern void* lbl_8042C1B0;
extern void* lbl_8042C1B4;
void __dl__FPv(void*);

void fn_8004014C()
{
	if (lbl_8042C1B0 != 0) {
		__dl__FPv(lbl_8042C1B0);
		lbl_8042C1B0 = 0;
	}
	if (lbl_8042C1B4 != 0) {
		__dl__FPv(lbl_8042C1B4);
		lbl_8042C1B4 = 0;
	}
}
}
