// Calls fn_80198330 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D230[];
void fn_80198330(int, int, int);
void fn_801521C0(int a0, int a1)
{
	fn_80198330((int)lbl_8028D230, (int)a0, (int)a1);
}
}
