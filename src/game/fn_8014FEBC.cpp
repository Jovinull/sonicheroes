// Calls fn_8014FFBC with the callback fn_8014F148 and a pointer to a zeroed local, and returns the local.

extern "C" {
void fn_8014F148();
void fn_8014FFBC(int, int, int*);

int fn_8014FEBC(int a)
{
	int z = 0;
	fn_8014FFBC(a, (int)fn_8014F148, &z);
	return z;
}
}
