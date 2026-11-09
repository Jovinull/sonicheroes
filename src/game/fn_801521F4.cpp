// Calls fn_80198A60 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D230[];
void fn_80198A60(int, int);
void fn_801521F4(int a0)
{
	fn_80198A60((int)lbl_8028D230, (int)a0);
}
}
