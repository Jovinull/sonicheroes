// Calls fn_8014FFBC with fixed or forwarded arguments and returns.

extern "C" {
void fn_800B8B08();
void fn_8014FFBC(int, int, int);
void fn_800B8ADC(int a0)
{
	fn_8014FFBC((int)a0, (int)fn_800B8B08, 0);
}
}
