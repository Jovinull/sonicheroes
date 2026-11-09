// Prints the debug string lbl_8024337C at position 0x20002 when lbl_8042C294 is set.

extern "C" {
extern int lbl_8042C294;
extern char lbl_8024337C[];
void njPrint__FiPCce(int, const char*, ...);

void fn_8005957C()
{
	if (lbl_8042C294 != 0) {
		njPrint__FiPCce(0x20002, lbl_8024337C);
	}
}
}
