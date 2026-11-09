// Calls fn_80198A90 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_80290640[];
void fn_80198A90(int, int, int, int, int, int);
void fn_801A4E40(int a0, int a1, int a2, int a3, int a4)
{
	fn_80198A90((int)lbl_80290640, (int)a0, (int)a1, (int)a2, (int)a3, (int)a4);
}
}
