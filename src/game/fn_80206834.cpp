// Calls fn_802063A0 with fixed or forwarded arguments and returns.

extern "C" {
void fn_80206890();
void fn_802063A0(int, int);
void fn_80206834(int a0)
{
	fn_802063A0((int)a0, (int)fn_80206890);
}
}
