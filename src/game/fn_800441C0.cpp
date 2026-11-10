// Starts action 0x35 unless 0x3F is already active, setting the float parameters and the optional vector target and angle.
struct Vec800441C0 {
	int x;
	int y;
	int z;
};
struct Obj800441C0 {
	unsigned char pad0[0x6F4];
	short f6F4;
	short f6F6;
	int f6F8;
	int f6FC;
	int f700;
	int f704;
	unsigned char pad708[0x30];
	int f738;
	int f73C;
	int f740;
	unsigned char pad744[0x30];
	short f774;
	unsigned char pad776[0xE];
	int f784;
	unsigned char pad788[0x38];
	float f7C0;
	float f7C4;
	float f7C8;
};

extern "C" {
extern float lbl_8042D1BC;

void fn_800441C0(Obj800441C0* o, Vec800441C0* v, int ang, float f)
{
	if ((o->f6F6 & 0x1000) == 0 || o->f6F4 != 0x3F) {
		o->f6F6 |= 0x1000;
		o->f6F4 = 0x35;
		o->f784 = 0x3E;
		o->f7C0 = f;
		{
			float z = lbl_8042D1BC;
			o->f7C8 = z;
			o->f7C4 = z;
		}
		if (v != 0) {
			o->f738 = v->x;
			o->f73C = 0x4000 - v->y;
			o->f740 = v->z;
			o->f6FC = o->f738;
			o->f700 = o->f73C;
			o->f704 = o->f740;
		}
		o->f774 = ang;
	}
}
}
