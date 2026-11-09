// Calls fn_80198A90 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_802904A0[];
void fn_80198A90(int, int, int, int, int, int);
void fn_8019D138(int a0, int a1, int a2, int a3, int a4)
{
	fn_80198A90((int)lbl_802904A0, (int)a0, (int)a1, (int)a2, (int)a3, (int)a4);
}
}
