// Calls fn_80198A90 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_80290628[];
void fn_80198A90(int, int, int, int, int, int);
void fn_801A17B4(int a0, int a1, int a2, int a3, int a4)
{
	fn_80198A90((int)lbl_80290628, (int)a0, (int)a1, (int)a2, (int)a3, (int)a4);
}
}
