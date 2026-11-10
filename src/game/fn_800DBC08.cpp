// Moves the point by the unit offset lbl_80242B38 scaled by the entity's value, normalises it via fn_8003EB18 and stores it at +0x54 unless flag 0x4000 is set.
struct V3_800DBC08 {
	float x;
	float y;
	float z;
};
struct A_800DBC08 {
	unsigned char pad0[6];
	short f6;
};
struct B_800DBC08 {
	unsigned char padb[0xC];
	V3_800DBC08 fC;
};
struct C_800DBC08 {
	unsigned char pad0[0x54];
	V3_800DBC08 f54;
	unsigned char pad60[0xE0];
	float f140;
};

extern "C" {
extern V3_800DBC08 lbl_80242B38;
void fn_8003EB18(A_800DBC08* a, V3_800DBC08* v, float f);

void fn_800DBC08(A_800DBC08* a, B_800DBC08* b, C_800DBC08* c)
{
	V3_800DBC08 sp;
	sp.x = b->fC.x;
	sp.y = b->fC.y;
	sp.z = b->fC.z;
	if ((a->f6 & 0x4000) == 0) {
		sp.x = sp.x + lbl_80242B38.x * c->f140;
		sp.y = sp.y + lbl_80242B38.y * c->f140;
		sp.z = sp.z + lbl_80242B38.z * c->f140;
		fn_8003EB18(a, &sp, c->f140);
		c->f54.x = sp.x;
		c->f54.y = sp.y;
		c->f54.z = sp.z;
	}
}
}
