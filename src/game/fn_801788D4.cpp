// Calls calloc with fixed or forwarded arguments and returns.

extern "C" {
void calloc(int, int);
void fn_801788D4(int a0, int a1, int a2)
{
	calloc((int)a1, (int)a2);
}
}
