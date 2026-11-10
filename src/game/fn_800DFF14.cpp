// Stores the three floats into the indexed record of lbl_802AD0B0.
struct Ent800DFF14 {
	unsigned char pad0[0xC];
	float fC;
	float f10;
	float f14;
};

extern "C" {
extern Ent800DFF14* lbl_802AD0B0[];

void fn_800DFF14(int i, float a, float b, float c)
{
	Ent800DFF14* e = lbl_802AD0B0[i];
	e->fC          = a;
	e->f10         = b;
	e->f14         = c;
}
}
