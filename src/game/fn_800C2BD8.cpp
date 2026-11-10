// Caches the ring count of the channel at +0x28 (clamped to 0..999), advances the float at +0x2C by lbl_8042DE5C and applies it through the callback pipeline.
struct Obj800C2BD8 {
	unsigned char pad0[0x28];
	unsigned char f28;
	unsigned char pad29[3];
	float f2C;
	unsigned char pad30[0xC];
	int f3C;
	int f40;
};

extern "C" {
extern unsigned int lbl_8042B3E8[2];
extern int num__10PARAM_RING[];
extern unsigned char fn_800C480C[];
extern float lbl_8042DE5C;
void fn_802033F4(unsigned int a);
void fn_80204144(unsigned int h, unsigned char* a, float* b);
void fn_802041EC(unsigned int a);

void fn_800C2BD8(Obj800C2BD8* o)
{
	float sp8;
	o->f3C = num__10PARAM_RING[(signed char)o->f28];
	if (o->f3C > 0x3E7) {
		o->f40 = 0x3E7;
	} else if (o->f3C < 0) {
		o->f40 = 0;
	} else {
		o->f40 = o->f3C;
	}
	o->f2C         = o->f2C + lbl_8042DE5C;
	unsigned int h = lbl_8042B3E8[(signed char)o->f28];
	if (h != 0) {
		sp8 = o->f2C;
		fn_80204144(h, fn_800C480C, &sp8);
		o->f2C = sp8;
		fn_802041EC(lbl_8042B3E8[(signed char)o->f28]);
		fn_802033F4(lbl_8042B3E8[(signed char)o->f28]);
	}
}
}
