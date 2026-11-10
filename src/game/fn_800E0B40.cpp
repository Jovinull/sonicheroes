// Starts action 0x25 on entity idx unless 0x3F is active: stores the angle, the float and the angle vector, and mirrors the direction into the position record.
struct V3_800E0B40 {
	float x;
	float y;
	float z;
};
struct I3_800E0B40 {
	int x;
	int y;
	int z;
};
struct St_800E0B40 {
	unsigned char pad0[4];
	short f4;
	short f6;
	unsigned char pad8[4];
	int fC;
	int f10;
	int f14;
};
struct Pos_800E0B40 {
	V3_800E0B40 f0;
	unsigned char pad0C[0x10];
	int f1C;
};
struct Ent_800E0B40 {
	unsigned char pad0[0x14];
	short f14;
	unsigned char pad16[0x4A];
	V3_800E0B40 f60;
};

extern "C" {
extern St_800E0B40* lbl_802AD090[];
extern Pos_800E0B40* lbl_802AD0B0[];
extern Ent_800E0B40* lbl_802AD0D0[];
extern float lbl_8042E1F0;
void fn_8003E9B4(St_800E0B40* s, V3_800E0B40* v);

void fn_800E0B40(int idx, I3_800E0B40* a, int ang, float f)
{
	V3_800E0B40 sp;
	St_800E0B40* st = lbl_802AD090[idx];
	Pos_800E0B40* p = lbl_802AD0B0[idx];
	Ent_800E0B40* e = lbl_802AD0D0[idx];
	if ((st->f6 & 0x1000) == 0 || st->f4 != 0x3F) {
		e->f14 = ang;
		st->f6 |= 0x1000;
		st->f4   = 0x25;
		sp.x     = lbl_8042E1F0;
		sp.y     = f;
		sp.z     = lbl_8042E1F0;
		e->f60.x = lbl_8042E1F0;
		e->f60.y = sp.y;
		e->f60.z = sp.z;
		st->fC   = a->x;
		st->f10  = 0x4000 - a->y;
		p->f1C   = st->f10;
		st->f14  = a->z;
		fn_8003E9B4(st, &sp);
		p->f0.x = sp.x;
		p->f0.y = sp.y;
		p->f0.z = sp.z;
	}
}
}
