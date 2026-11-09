// Calls fn_8015B8E8 with the arguments swapped and returns the first argument.

extern "C" {
void fn_8015B8E8(int, int);

int fn_8015B280(int a, int b)
{
	fn_8015B8E8(b, a);
	return a;
}
}
