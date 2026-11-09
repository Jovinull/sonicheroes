// Calls fn_8015BD84 with the arguments swapped and returns the first argument.

extern "C" {
void fn_8015BD84(int, int);

int fn_8015B1F8(int a, int b)
{
	fn_8015BD84(b, a);
	return a;
}
}
