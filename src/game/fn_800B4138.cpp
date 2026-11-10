// Resets a controller-slot record to its defaults (ids -1, cleared bytes/shorts, default float).
struct Rec800B4138 {
	unsigned char f0;
	signed char f1;
	signed char f2;
	unsigned char f3;
	unsigned char f4;
	unsigned char f5;
	unsigned char f6;
	unsigned char f7;
	unsigned char f8;
	unsigned char f9;
	unsigned char padA[2];
	int fC;
	short f10;
	short f12;
	short f14;
	short f16;
	short f18;
	unsigned char pad1A[2];
	int f1C;
	float f20;
	float f24;
	float f28;
	float f2C;
	float f30;
	int f34;
};

extern "C" {
extern float lbl_8042DCE8;

void fn_800B4138(Rec800B4138* r)
{
	float z = z;
	r->f1   = -1;
	r->f2   = -1;
	r->f3   = 0;
	r->f4   = 0;
	r->f6   = 0;
	r->f5   = 0;
	r->f7   = 0;
	r->f8   = 0;
	r->f9   = 0;
	r->fC   = 0;
	r->f10  = 0;
	r->f12  = 0;
	r->f14  = 0;
	r->f16  = 0;
	r->f18  = 0;
	r->f1C  = 0;
	{
		float z = lbl_8042DCE8;
		r->f28  = z;
		r->f24  = z;
		r->f20  = z;
		r->f2C  = z;
		r->f30  = z;
		r->f34  = 0;
	}
}
}
