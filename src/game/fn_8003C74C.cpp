// Calls fn_8014FFBC with fixed or forwarded arguments and returns.

extern "C" {
void fn_8003C778();
void fn_8014FFBC(int, int, int);
void fn_8003C74C(int a0, int a1)
{
	fn_8014FFBC((int)a0, (int)fn_8003C778, (int)a1);
}
}
