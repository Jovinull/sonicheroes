// Calls fn_801B0990 with fixed or forwarded arguments and returns.

extern "C" {
void fn_801B0990(int, int, int, int);
void fn_801B0B30(int a0, int a1)
{
	fn_801B0990((int)a0, (int)a1, 0, 0);
}
}
