// Calls fn_80159E18 with fixed or forwarded arguments and returns.

extern "C" {
void fn_800B8BA4();
void fn_80159E18(int, int, int);
void fn_800B8B78(int a0)
{
	fn_80159E18((int)a0, (int)fn_800B8BA4, 0);
}
}
