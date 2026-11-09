// Calls fn_8014FFBC with the callback fn_800B8C48 and a pointer to a local copy of the second argument.

extern "C" {
void fn_800B8C48();
void fn_8014FFBC(int, int, int);

void fn_800B8BEC(int a, int b)
{
	int local = b;
	fn_8014FFBC(a, (int)fn_800B8C48, (int)&local);
}
}
