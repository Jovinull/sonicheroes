// Rotates the entity's heading towards the target angle (limit 0x2000) and re-applies the vector stored at +0x60 through fn_8003E9B4 / fn_8003EB18.
struct V3_800E17F8 {
	float x;
	float y;
	float z;
};
struct Own800E17F8 {
	unsigned char pad0[0x10];
	int f10;
};
struct Ent800E17F8 {
	unsigned char pad0[0x60];
	V3_800E17F8 f60;
};

int AdjustAngle(int a, int b, int c);

extern "C" {
void fn_8003E9B4(Own800E17F8* o, V3_800E17F8* v);
void fn_8003EB18(Own800E17F8* o, V3_800E17F8* v);

void fn_800E17F8(Own800E17F8* o, int unused, Ent800E17F8* e, int ang)
{
	V3_800E17F8 sp;
	sp.x = e->f60.x;
	sp.y = e->f60.y;
	sp.z = e->f60.z;
	fn_8003E9B4(o, &sp);
	o->f10 = AdjustAngle(o->f10, ang, 0x2000);
	fn_8003EB18(o, &sp);
	e->f60.x = sp.x;
	e->f60.y = sp.y;
	e->f60.z = sp.z;
}
}
