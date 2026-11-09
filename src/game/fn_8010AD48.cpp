// Loads the clump animation lbl_8025AEA4 into lbl_8042C5B0 and clears the byte flags at lbl_8042C5B4 and the words at lbl_803E7258.

extern "C" {
extern int lbl_8042C5B0;
extern unsigned char lbl_8042C5B4[4];
extern int lbl_803E7258[4];
extern char lbl_8025AEA4[];
int objPointerReadFromClumpAnim__FPc(char*);

void fn_8010AD48()
{
	lbl_8042C5B0    = objPointerReadFromClumpAnim__FPc(lbl_8025AEA4);
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
