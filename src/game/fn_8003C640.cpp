// Calls fn_8014FFBC with fixed or forwarded arguments and returns.

extern "C" {
void fn_8003C66C();
void fn_8014FFBC(int, int, int);
void fn_8003C640(int a0)
{
	fn_8014FFBC((int)a0, (int)fn_8003C66C, 0);
}
}
