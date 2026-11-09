// Calls fn_8014FFBC with fixed or forwarded arguments and returns.

extern "C" {
void fn_800BDF5C();
void fn_8014FFBC(int, int, int);
void fn_800BDF30(int a0)
{
	fn_8014FFBC((int)a0, (int)fn_800BDF5C, 0);
}
}
