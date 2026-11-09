// Stores the first argument in the word that fn_80194430(third) returns, and returns the first argument.

extern "C" {
int* fn_80194430(int);

int fn_80202164(int a, int b, int c)
{
	int* p = fn_80194430(c);
	*p     = a;
	return a;
}
}
