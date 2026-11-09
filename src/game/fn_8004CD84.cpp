// Copies lbl_8042C220 into lbl_8042C21C and lbl_8042C228 into lbl_8042C224.

extern "C" {
extern int lbl_8042C21C;
extern int lbl_8042C220;
extern int lbl_8042C224;
extern int lbl_8042C228;

void fn_8004CD84()
{
	lbl_8042C21C = lbl_8042C220;
	lbl_8042C224 = lbl_8042C228;
}
}
