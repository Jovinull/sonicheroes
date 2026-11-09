// Calls fn_801982B0 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_802905F8[];
void fn_801982B0(int, int, int, int, int);
void fn_8019A1DC(int a0, int a1, int a2, int a3)
{
	fn_801982B0((int)lbl_802905F8, (int)a0, (int)a1, (int)a2, (int)a3);
}
}
