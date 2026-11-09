// Looks up the entry index for the given name and stores it, or -1 when no name is given.
struct Obj8015271C {
	unsigned char pad0[6];
	short f6;
};

extern "C" {
int fn_80155040(int a, int b);
int fn_80154F10(int a, int b);

int fn_8015271C(int a, Obj8015271C* o, int c)
{
	int v;
	if (c != 0) {
		v = fn_80155040(a + 0x20, c);
		if (v < 0) {
			v = fn_80154F10(a + 0x20, c);
			if (v < 0) {
				return 0;
			}
		}
		o->f6 = v;
	} else {
		o->f6 = -1;
	}
	return a;
}
}
