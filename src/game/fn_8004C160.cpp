// Blends the object's vector toward the target (adds it and scales) and eases its two angles halfway towards the target's.
int DiffAngle(int a, int b);
int AdjustAngle(int a, int b, int c);

struct Tgt8004C160 {
	float f0;
	float f4;
	float f8;
	int fC;
	int f10;
};
struct Obj8004C160 {
	int f0;
	unsigned char pad4[0xC];
	float f10;
	float f14;
	float f18;
	int f1C;
	int f20;
};

extern "C" {
extern Tgt8004C160* volatile lbl_8042C208;
extern float lbl_8042D298;

void fn_8004C160(Obj8004C160* o)
{
	float t = o->f10 + lbl_8042C208->f0;
	float k = lbl_8042D298;
	o->f10  = t * k;
	t       = o->f14 + lbl_8042C208->f4;
	o->f14  = t * k;
	t       = o->f18 + lbl_8042C208->f8;
	o->f18  = t * k;
	int d   = DiffAngle(o->f1C, lbl_8042C208->fC) >> 1;
	int a   = lbl_8042C208->fC;
	int b   = o->f1C;
	o->f1C  = AdjustAngle(a, b, d);
	d       = DiffAngle(o->f20, lbl_8042C208->f10) >> 1;
	a       = lbl_8042C208->f10;
	b       = o->f20;
	o->f20  = AdjustAngle(a, b, d);
	o->f0   = 1;
}
}
