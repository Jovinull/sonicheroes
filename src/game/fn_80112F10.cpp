// Releases the object held in lbl_8042C620 through fn_801A46D0 and clears the pointer.

extern "C" {
extern int lbl_8042C620;
void fn_801A46D0(int);

void fn_80112F10()
{
	fn_801A46D0(lbl_8042C620);
	lbl_8042C620 = 0;
}
}
