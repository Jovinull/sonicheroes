// Calls fn_8015E920 with fixed or forwarded arguments and returns.

extern "C" {
void fn_8015E920(int, int);
void fn_8015B448(int a0, int a1, int a2)
{
	fn_8015E920((int)a0, (int)a2);
}
}
