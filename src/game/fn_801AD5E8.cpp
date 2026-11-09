// Creates the object (fn_801A17B4(0x34, 0x40C, 0, 0, 0)) and stores it in lbl_8042CA48.

extern "C" {
extern int lbl_8042CA48;
int fn_801A17B4(int, int, int, int, int);

void fn_801AD5E8()
{
	lbl_8042CA48 = fn_801A17B4(0x34, 0x40c, 0, 0, 0);
}
}
