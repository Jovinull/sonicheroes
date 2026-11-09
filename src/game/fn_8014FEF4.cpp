// Calls fn_801500BC with the callback fn_8014F158 and a pointer to a zeroed local, and returns the local.

extern "C" {
void fn_8014F158();
void fn_801500BC(int, int, int*);

int fn_8014FEF4(int a)
{
	int z = 0;
	fn_801500BC(a, (int)fn_8014F158, &z);
	return z;
}
}
