// Resets the character's state to 2 after a landing: picks the next action unless the state was 4 or 0xA, and clears or sets the state flag bits.
struct St8006AAB0 {
	short f0;
	unsigned char pad2[4];
	short f6;
};
struct Obj8006AAB0 {
	unsigned char pad0[0x12];
	short f12;
	unsigned char pad14[0x50];
	float f64;
	unsigned char pad68[0x78];
	float fE0;
	unsigned char padE4[0x6A];
	short f14E;
	unsigned char pad150[0xDC];
	unsigned int f22C;
	unsigned char pad230[0xC];
	float f23C;
	float f240;
};

extern "C" {
extern float lbl_8042D510;
double __fabs(double x);
void fn_8004675C();
void fn_80046A04(int a);

void fn_8006AAB0(int a, St8006AAB0* st, int unused, Obj8006AAB0* o)
{
	short t = st->f0;
	if (t == 4 || t == 0xA) {
		o->f14E = 0x39;
	} else {
		int r;
		o->f64 = o->fE0;
		fn_8004675C();
		if ((o->f22C & 2) != 0 && (float)__fabs(o->f23C - o->f240) > lbl_8042D510) {
			r = 1;
		} else {
			r = 0;
		}
		if (r == 0) {
			fn_80046A04(a);
		}
	}
	st->f0 = 2;
	st->f6 &= ~0x2500;
	st->f6 |= 0x400;
	st->f6 &= ~2;
	o->f12 = 0;
}
}
