// Calls fn_80209EA8 with 1 for mode 0 and 0 for mode 1; returns 0x0D000001 when uninitialised, 0x03000001 for any other mode, else 0.

extern "C" {
extern unsigned lbl_8042CF6C;
void fn_80209EA8(int);

int fn_8020B540(int k)
{
	if (lbl_8042CF6C == 0) {
		return 0x0d000001;
	}
	switch (k) {
		case 0:
			fn_80209EA8(1);
			break;
		case 1:
			fn_80209EA8(0);
			break;
		default:
			return 0x03000001;
	}
	return 0;
}
}
