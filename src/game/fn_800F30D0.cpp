// Callback: if fn_8013F484(a) gives a result, stores it in *out and returns 0; otherwise re-registers itself with fn_8019EB10(a, fn_800F30D0, out) and returns a.

extern "C" {
unsigned fn_8013F484(int);
void fn_8019EB10(int, int (*)(int, unsigned*), unsigned*);

int fn_800F30D0(int a, unsigned* out)
{
	unsigned r = fn_8013F484(a);
	if (r == 0) {
		fn_8019EB10(a, fn_800F30D0, out);
		return a;
	}
	*out = r;
	return 0;
}
}
