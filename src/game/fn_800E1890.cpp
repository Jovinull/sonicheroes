// Rotates the entity's heading towards the target angle (limit lbl_8042B6B0) and re-applies the vector stored at +0x60 through fn_8003E9B4 / fn_8003EB18.
struct V3_800E1890 {
	float x;
	float y;
	float z;
};
struct Own800E1890 {
	unsigned char pad0[0x10];
	int f10;
};
struct Ent800E1890 {
	unsigned char pad0[0x60];
	V3_800E1890 f60;
};

int AdjustAngle(int a, int b, int c);
extern "C" int lbl_8042B6B0;
extern "C" {
void fn_8003E9B4(Own800E1890* o, V3_800E1890* v);
void fn_8003EB18(Own800E1890* o, V3_800E1890* v);

void fn_800E1890(Own800E1890* o, int unused, Ent800E1890* e, int ang)
{
	V3_800E1890 sp;
	sp.x = e->f60.x;
	sp.y = e->f60.y;
	sp.z = e->f60.z;
	fn_8003E9B4(o, &sp);
	o->f10 = AdjustAngle(o->f10, ang, lbl_8042B6B0);
	fn_8003EB18(o, &sp);
	e->f60.x = sp.x;
	e->f60.y = sp.y;
	e->f60.z = sp.z;
}
}
