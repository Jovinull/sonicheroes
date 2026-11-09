// Calls fn_801982F4 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8028D230[];
void fn_801982F4(int, int, int);
void fn_8015218C(int a0, int a1)
{
	fn_801982F4((int)lbl_8028D230, (int)a0, (int)a1);
}
}
