// Clears the four-word table at lbl_803E7258, its four-byte flag array and the
// counter next to it.

extern "C" {
extern int lbl_8042C5B0;
extern unsigned char lbl_8042C5B4[4];
extern int lbl_803E7258[4];
void fn_8010AD10()
{
	lbl_8042C5B0    = 0;
	lbl_8042C5B4[0] = 0;
	lbl_803E7258[0] = 0;
	lbl_8042C5B4[1] = 0;
	lbl_803E7258[1] = 0;
	lbl_8042C5B4[2] = 0;
	lbl_803E7258[2] = 0;
	lbl_8042C5B4[3] = 0;
	lbl_803E7258[3] = 0;
}
}
