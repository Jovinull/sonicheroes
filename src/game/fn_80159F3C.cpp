// Calls fn_80198A90 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D2E8[];
void fn_80198A90(int, int, int, int, int, int);
void fn_80159F3C(int a0, int a1, int a2, int a3, int a4)
{
	fn_80198A90((int)lbl_8028D2E8, (int)a0, (int)a1, (int)a2, (int)a3, (int)a4);
}
}
