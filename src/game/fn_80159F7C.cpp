// Calls fn_801982B0 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D2E8[];
void fn_801982B0(int, int, int, int, int);
void fn_80159F7C(int a0, int a1, int a2, int a3)
{
	fn_801982B0((int)lbl_8028D2E8, (int)a0, (int)a1, (int)a2, (int)a3);
}
}
