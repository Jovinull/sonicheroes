// Looks up the result for the handle at 4 (fn_8013F484), registering the callback fn_800F30D0 to retry when there is none yet; returns the result.

extern "C" {
struct Obj800F3074 {
	unsigned char pad[4];
	int f4;
};
unsigned fn_8013F484(int);
int fn_800F30D0(int, unsigned*);
void fn_8019EB10(int, int (*)(int, unsigned*), unsigned*);

unsigned fn_800F3074(Obj800F3074* o)
{
	unsigned sp = 0;
	unsigned r  = fn_8013F484(o->f4);
	sp          = r;
	if (r == 0) {
		fn_8019EB10(o->f4, fn_800F30D0, &sp);
	}
	return sp;
}
}
