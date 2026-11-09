// Creates the object (fn_801A4E40 with the two callbacks) and stores it in lbl_8042CA60.

extern "C" {
extern int lbl_8042CA60;
void fn_801B1BF8();
void fn_801B1C0C();
int fn_801A4E40(int, int, void (*)(), void (*)(), int);

void fn_801B1CCC()
{
	lbl_8042CA60 = fn_801A4E40(0x24, 0x40c, fn_801B1BF8, fn_801B1C0C, 0);
}
}
