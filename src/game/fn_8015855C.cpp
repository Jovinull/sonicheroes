// Calls fn_80157F50 with fixed or forwarded arguments and returns.

extern "C" {
void fn_80157F50(int, int, int);
void fn_8015855C(int a0)
{
	fn_80157F50((int)a0, 0, 1);
}
}
