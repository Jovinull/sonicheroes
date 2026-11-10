// Collects the optional outputs of an active entry and returns which ones were written.
struct Obj8017CB9C {
	unsigned char pad0[8];
	unsigned int f8;
	unsigned char padC[0xA];
	unsigned short f16;
	unsigned char pad18;
	unsigned char f19;
	unsigned char pad1A[0x32];
	int f4C;
};

extern "C" {
int fn_8017CB9C(unsigned int a, Obj8017CB9C* o, int* p5, int* p6, void** p7)
{
	int r = 0;
	if (a != 0 && o != 0 && (o->f8 & 0x10)) {
		if (o->f19 == 3) {
			if (p5 != 0) {
				r |= 0x10;
				*p5 = o->f4C;
			}
			if (p7 != 0) {
				*p7 = (char*)o + 0x50;
			}
		} else {
			if (p7 != 0) {
				r |= 0x10;
				*p7 = (char*)o + 0x50;
			}
			if (p5 != 0) {
				*p5 = 0;
			}
		}
		if (p6 != 0) {
			*p6 = o->f16;
			r |= 0x10;
		}
	}
	return r;
}
}
