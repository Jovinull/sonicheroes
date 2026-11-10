// Fills the single pending marker record lbl_80304558 (position, colour, value, float) and flags it as set.
struct V2_800C4B6C {
	float x;
	float y;
};
struct Cfg800C4B6C {
	float f0;
	float f4;
	unsigned char f8;
	unsigned char f9;
	unsigned char fA;
	unsigned char fB;
	int fC;
	float f10;
};

extern "C" {
extern Cfg800C4B6C lbl_80304558;
extern int lbl_8042C450;

void fn_800C4B6C(V2_800C4B6C* pos, int val, unsigned char* col, float f)
{
	lbl_80304558.f8  = col[0];
	lbl_80304558.f9  = col[1];
	lbl_80304558.fA  = col[2];
	lbl_80304558.fB  = col[3];
	lbl_80304558.f0  = pos->x;
	lbl_80304558.f4  = pos->y;
	lbl_80304558.f10 = f;
	lbl_80304558.fC  = val;
	lbl_8042C450     = 1;
}
}
