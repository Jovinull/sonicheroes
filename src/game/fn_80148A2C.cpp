// Reads a 4-byte flag from the stream arg0; returns 0 on failure, otherwise runs fn_801491A8(arg2) when the flag is set and returns arg0.

extern "C" {
unsigned fn_80193884(void*, void*, int);
void fn_801491A8(int);

void* fn_80148A2C(void* a, int unused, int c)
{
	int sp8;
	if (fn_80193884(a, &sp8, 4) == 0) {
		return 0;
	}
	if (sp8 != 0) {
		fn_801491A8(c);
	}
	return a;
}
}
