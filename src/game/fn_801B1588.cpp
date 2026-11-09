// Calls fn_801B11A4 with fixed or forwarded arguments and returns.

extern "C" {
extern int lbl_8042CA58;
void fn_801B11A4(int);
void fn_801B1588()
{
	fn_801B11A4(lbl_8042CA58);
}
}
