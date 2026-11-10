// Computes the heading towards the target (atan2 of the position deltas), stores it as an angle at +0x174 and compares it with the current one.
struct Obj800A5A54 {
	unsigned char pad0[0x140];
	float f140;
	unsigned char pad144[4];
	float f148;
	unsigned char pad14C[4];
	int f150;
	unsigned char pad154[0x20];
	int f174;
	unsigned char pad178[0x54];
	float f1CC;
	unsigned char pad1D0[4];
	float f1D4;
};

int DiffAngle(int a, int b);
extern "C" double atan2(double y, double x);

extern float lbl_8042DA7C;

extern "C" void fn_800A5A54(Obj800A5A54* o)
{
	float t = (float)atan2(o->f1CC - o->f140, o->f1D4 - o->f148);
	o->f174 = (int)(lbl_8042DA7C * t);
	DiffAngle(o->f174, o->f150);
}
