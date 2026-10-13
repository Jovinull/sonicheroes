// A static initializer: lbl_8042C458 (volatile) is first set to SEQUENCE's
// vtable and then to lbl_80254C5C, as an inlined constructor chain leaves it.

extern "C" {
extern unsigned char __vt__8SEQUENCE[];
extern unsigned char lbl_80254C5C[];
extern unsigned char* volatile lbl_8042C458;

void fn_800C8E84(void)
{
	lbl_8042C458 = __vt__8SEQUENCE;
	lbl_8042C458 = lbl_80254C5C;
}
}

__declspec(section ".ctors") void (*const fn800C8E84CtorEntry)(void) = fn_800C8E84;
