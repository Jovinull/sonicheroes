// Calls fn_801A491C on the argument and returns the argument.

extern "C" {
void fn_801A491C(int);

int fn_8019B714(int a)
{
	fn_801A491C(a);
	return a;
}
}
