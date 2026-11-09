// Calls fn_8020641C with fixed or forwarded arguments and returns.

extern "C" {
void fn_80206890();
void fn_8020641C(int, int, int);
void fn_8020685C(int a0, int a1)
{
	fn_8020641C((int)a1, (int)a0, (int)fn_80206890);
}
}
