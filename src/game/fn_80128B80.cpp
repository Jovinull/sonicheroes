// Clears the two four-word tables at lbl_80289F80 / lbl_80289F90 and the value
// that goes with them.

extern "C" {
extern int lbl_80289F80[4];
extern int lbl_80289F90[4];
extern int lbl_8042C730;
void fn_80128B80()
{
	lbl_80289F80[0] = 0;
	lbl_80289F90[0] = 0;
	lbl_80289F80[1] = 0;
	lbl_80289F90[1] = 0;
	lbl_80289F80[2] = 0;
	lbl_80289F90[2] = 0;
	lbl_80289F80[3] = 0;
	lbl_80289F90[3] = 0;
	lbl_8042C730    = 0;
}
}
