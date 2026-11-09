// Installs the two callbacks fn_80112BB0 and fn_801127FC in lbl_8042C0D8 and lbl_8042C0DC.

extern "C" {
void fn_80112BB0();
void fn_801127FC();
extern void (*lbl_8042C0D8)();
extern void (*lbl_8042C0DC)();

void fn_80112F80()
{
	lbl_8042C0D8 = fn_80112BB0;
	lbl_8042C0DC = fn_801127FC;
}
}
