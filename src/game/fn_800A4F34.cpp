// Applies gravity to the Y velocity (or zeroes it when flag 2 is set), clamps the horizontal speed to +0x1B8 and raises Y to the minimum at +0x1B4.
struct Blk800A4F34 {
	unsigned char b[12];
};
struct V3_800A4F34 {
	float x;
	float y;
	float z;
};
struct Obj800A4F34 {
	unsigned char pad0[0x106];
	unsigned short f106;
	unsigned char pad108[0x50];
	V3_800A4F34 v158;
	unsigned char pad164[0x44];
	float f1A8;
	unsigned char pad1AC[8];
	float f1B4;
	float f1B8;
};

extern "C" {
extern float lbl_8042DA74;
void fn_801990E0(V3_800A4F34* a, V3_800A4F34* b);
float fn_801991B4(V3_800A4F34* a);

void fn_800A4F34(Obj800A4F34* o)
{
	if ((o->f106 & 2) == 0) {
		o->v158.y = o->v158.y + o->f1A8;
	} else {
		o->v158.y = lbl_8042DA74;
	}
	V3_800A4F34 sp;
	*(Blk800A4F34*)&sp = *(Blk800A4F34*)&o->v158;
	sp.y               = lbl_8042DA74;
	if (fn_801991B4(&sp) > o->f1B8) {
		fn_801990E0(&sp, &sp);
		sp.x      = sp.x * o->f1B8;
		sp.y      = sp.y * o->f1B8;
		sp.z      = sp.z * o->f1B8;
		o->v158.x = sp.x;
		o->v158.z = sp.z;
	}
	if (o->v158.y < o->f1B4) {
		o->v158.y = o->f1B4;
	}
}
}
