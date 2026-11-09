// Resets with fn_801B2EA0(0) and, if the pointer in *p is set, releases it with fn_801B3A10 and clears it.

extern "C" {
void fn_801B3A10(unsigned);
int fn_801B2EA0(int);

void fn_801B7FE4(unsigned* p)
{
	fn_801B2EA0(0);
	if (*p != 0) {
		fn_801B3A10(*p);
		*p = 0;
	}
}
}
