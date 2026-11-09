// Calls fn_8015E858 with fixed or forwarded arguments and returns.

extern "C" {
void fn_8015E858(int, int);
void fn_8015B3C0(int a0, int a1, int a2)
{
	fn_8015E858((int)a0, (int)a2);
}
}
