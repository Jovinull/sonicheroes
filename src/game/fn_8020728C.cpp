// Calls fn_802063A0 with fixed or forwarded arguments and returns.

extern "C" {
void fn_802072B4();
void fn_802063A0(int, int);
void fn_8020728C(int a0)
{
	fn_802063A0((int)a0, (int)fn_802072B4);
}
}
