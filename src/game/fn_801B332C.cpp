// Calls fn_801B3414 on the argument and returns the argument.

extern "C" {
void fn_801B3414(int);

int fn_801B332C(int a)
{
	fn_801B3414(a);
	return a;
}
}
