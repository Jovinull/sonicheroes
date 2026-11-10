// Appends a marker record (position, colour, value, float) to the 16-entry queue lbl_80304418 if it is not full.
struct V2_800C4BB8 {
	float x;
	float y;
};
struct Cfg800C4BB8 {
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
extern Cfg800C4BB8 lbl_80304418[];
extern int lbl_8042C44C;

void fn_800C4BB8(V2_800C4BB8* pos, int val, unsigned char* col, float f)
{
	if (lbl_8042C44C < 0x10) {
		Cfg800C4BB8* c = &lbl_80304418[lbl_8042C44C];
		c->f8          = col[0];
		c->f9          = col[1];
		c->fA          = col[2];
		c->fB          = col[3];
		c->f0          = pos->x;
		c->f4          = pos->y;
		c->f10         = f;
		c->fC          = val;
		lbl_8042C44C += 1;
	}
}
}
