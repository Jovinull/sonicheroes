// Runs fn_80209CDC(0, 2) when the audio system is initialised; returns 0x0D000001 otherwise, 0 on success.

extern "C" {
extern unsigned lbl_8042CF6C;
void fn_80209CDC(int, int);

int fn_8020AD88(void)
{
	if (lbl_8042CF6C == 0) {
		return 0x0d000001;
	}
	fn_80209CDC(0, 2);
	return 0;
}
}
