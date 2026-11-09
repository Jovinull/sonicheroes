// Calls fn_801982B0 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D260[];
void fn_801982B0(int, int, int, int, int);
void fn_8015301C(int a0, int a1, int a2, int a3)
{
	fn_801982B0((int)lbl_8028D260, (int)a0, (int)a1, (int)a2, (int)a3);
}
}
