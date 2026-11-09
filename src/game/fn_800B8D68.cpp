// Calls fn_80149214 on the argument and returns the argument.

extern "C" {
int fn_80149214(int);

int fn_800B8D68(int a)
{
	fn_80149214(a);
	return a;
}
}
