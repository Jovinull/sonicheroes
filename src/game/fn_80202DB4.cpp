// Runs the per-flag handler chain for every enabled flag bit and returns the object.
struct Obj80202DB4 {
	unsigned char pad0[4];
	int f4;
	unsigned int f8;
};

extern "C" {
int fn_80173A4C(int a, int b);
void fn_801733C0(int a, int b);

Obj80202DB4* fn_80202DB4(Obj80202DB4* o, int a)
{
	int n;
	int t;
	if (o->f8 & 1) {
		t = fn_80173A4C(a, o->f4);
		n = 1;
		if (o->f8 & 2) {
			fn_801733C0(fn_80173A4C(t, 1), 1);
			n = 2;
		}
		if (o->f8 & 4) {
			fn_801733C0(fn_80173A4C(t, n), 0);
			n += 1;
		}
		if (o->f8 & 8) {
			fn_801733C0(fn_80173A4C(t, n), 0);
		}
	}
	return o;
}
}
