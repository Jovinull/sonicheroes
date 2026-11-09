// Calls memcpy with fixed or forwarded arguments and returns.

extern "C" {
void memcpy(int, int, int);
void fn_80173048(int a0, int a1)
{
	memcpy((int)a0, (int)a1, 256);
}
}
