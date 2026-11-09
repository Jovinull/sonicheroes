// Object teardown: clears lbl_8042C1D0, sets both words of lbl_8042AF50 to 1 and frees the object when the flags are positive; returns the object.

extern "C" {
extern int lbl_8042C1D0;
struct Pair8004BDC0 {
	int a;
	int b;
};
extern Pair8004BDC0 lbl_8042AF50;
void __dl__FPv(void*);

void* fn_8004BDC0(void* o, short flags)
{
	if (o != 0) {
		lbl_8042C1D0   = 0;
		lbl_8042AF50.a = 1;
		lbl_8042AF50.b = 1;
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
