// Reads a 4-byte flag from stream arg0 (initial value: whether arg1 is non-null); if set, requires fn_8019AAFC(arg1, arg0) to succeed; returns arg0 or 0.

extern "C" {
unsigned fn_80193474(int, int*, int);
unsigned fn_8019AAFC(int, int);

int fn_80147DFC(int a, int b)
{
	int sp8;
	sp8 = (b != 0);
	if (fn_80193474(a, &sp8, 4) == 0) {
		return 0;
	}
	if (sp8 != 0 && fn_8019AAFC(b, a) == 0) {
		return 0;
	}
	return a;
}
}
