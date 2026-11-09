// Calls fn_8015B9CC with the arguments swapped and returns the first argument.

extern "C" {
void fn_8015B9CC(int, int);

int fn_8015B170(int a, int b)
{
	fn_8015B9CC(b, a);
	return a;
}
}
