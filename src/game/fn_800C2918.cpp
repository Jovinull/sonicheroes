// Clamps the value at +0x34, scales it into +0x2C, runs the value through the callback pipeline and applies it to the handle of channel +0x28.
struct Obj800C2918 {
	unsigned char pad0[0x28];
	unsigned char f28;
	unsigned char pad29[3];
	float f2C;
	unsigned char pad30[4];
	float f34;
	float f38;
};

extern "C" {
extern unsigned int lbl_8042B3F8[2];
extern unsigned char fn_800C480C[];
extern float lbl_8042DE54;
extern float lbl_8042DEA0;
void fn_802033F4(unsigned int a);
void fn_80204144(unsigned int h, unsigned char* a, float* b);
void fn_802041EC(unsigned int a);

void fn_800C2918(Obj800C2918* o)
{
	float sp8;
	float t = o->f34;
	if (t > lbl_8042DEA0) {
		o->f34 = lbl_8042DEA0;
	} else if (t < lbl_8042DE54) {
		o->f34 = lbl_8042DE54;
	}
	o->f2C         = o->f34 * o->f38;
	unsigned int h = lbl_8042B3F8[(signed char)o->f28];
	if (h != 0) {
		sp8 = o->f2C;
		fn_80204144(h, fn_800C480C, &sp8);
		o->f2C = sp8;
		fn_802041EC(lbl_8042B3F8[(signed char)o->f28]);
		fn_802033F4(lbl_8042B3F8[(signed char)o->f28]);
	}
}
}
