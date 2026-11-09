// Calls fn_801982B0 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D2D0[];
void fn_801982B0(int, int, int, int, int);
void fn_80158998(int a0, int a1, int a2, int a3)
{
	fn_801982B0((int)lbl_8028D2D0, (int)a0, (int)a1, (int)a2, (int)a3);
}
}
