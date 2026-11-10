// Rotates the attached model around the Z axis, decrements the countdown byte at +0x28 by 8 (floored at 0) and sets flag 1 when it reaches 0.
struct Sub800F50D8 {
	unsigned char pad0[4];
	int f4;
};
struct Obj800F50D8 {
	unsigned char pad0[4];
	unsigned short f4;
	unsigned char pad6[0x22];
	unsigned char f28;
	unsigned char pad29[3];
	Sub800F50D8* f2C;
};

extern "C" {
extern unsigned char AxisZ[];
extern float lbl_8042E4FC;
void fn_8019E880(int a);
void fn_8019ED68(int a, unsigned char* b, float d, int c);

void fn_800F50D8(Obj800F50D8* o)
{
	int h = o->f2C->f4;
	int v;
	fn_8019ED68(h, AxisZ, lbl_8042E4FC, 1);
	fn_8019E880(h);
	v = o->f28;
	v -= 8;
	if (v < 0) {
		v = 0;
	}
	o->f28 = v;
	if (o->f28 == 0) {
		o->f4 |= 1;
	}
}
}
