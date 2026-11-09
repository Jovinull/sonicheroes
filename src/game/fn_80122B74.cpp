// Clears lbl_8042C718 and lbl_8042C71C.

extern "C" {
extern int lbl_8042C718;
extern int lbl_8042C71C;

void fn_80122B74()
{
	lbl_8042C718 = 0;
	lbl_8042C71C = 0;
}
}
