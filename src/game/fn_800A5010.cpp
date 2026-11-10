// Clamps the horizontal part of the velocity vector at +0x158 to the maximum at +0x1B8 and raises the Y component to the minimum at +0x1B4.
struct Blk800A5010 {
	unsigned char b[12];
};
struct V3_800A5010 {
	float x;
	float y;
	float z;
};
struct Obj800A5010 {
	unsigned char pad0[0x106];
	unsigned short f106;
	unsigned char pad108[0x50];
	V3_800A5010 v158;
	unsigned char pad164[0x44];
	float f1A8;
	unsigned char pad1AC[8];
	float f1B4;
	float f1B8;
};

extern "C" {
extern float lbl_8042DA74;
void fn_801990E0(V3_800A5010* a, V3_800A5010* b);
float fn_801991B4(V3_800A5010* a);

void fn_800A5010(Obj800A5010* o)
{
	V3_800A5010 sp;
	*(Blk800A5010*)&sp = *(Blk800A5010*)&o->v158;
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
