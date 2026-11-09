// In mode 2, takes the counter from lbl_8029C310 (+0x2C) when fn_80018EA8 reports ready (minus one, floored at 0, unless arg2 is set) and stores arg1 at +4.

extern "C" {
struct Pair801169A4 {
	int f0;
	int f4;
};
struct Glob801169A4 {
	unsigned char pad[0x28];
	signed char c28;
};
struct Src801169A4 {
	unsigned char pad[0x2c];
	int f2c;
};
extern Glob801169A4* lbl_8042C180;
extern Src801169A4 lbl_8029C310;
int fn_80018EA8(void*);

void fn_801169A4(Pair801169A4* o, int a, int b)
{
	if (lbl_8042C180->c28 == 2) {
		if (fn_80018EA8(&lbl_8029C310) == 0) {
			o->f0 = lbl_8029C310.f2c;
			if (b == 0) {
				o->f0 = o->f0 - 1;
				if (o->f0 < 0) {
					o->f0 = 0;
				}
			}
		}
		o->f4 = a;
	}
}
}
