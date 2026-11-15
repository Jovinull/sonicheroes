// Transforms the player slot's world position into the output vector: zeroes X/Z, copies the
// slot object's float at +0x148 into Y, then runs fn_8003E9B4 on the paired slot object.

struct Vec800AB3D8 {
	float x;
	float y;
	float z;
};
struct Ent800AB3D8 {
	unsigned char pad0[0x148];
	float f148;
};

extern "C" {
extern Ent800AB3D8* lbl_802AD0D0[];
extern Ent800AB3D8* lbl_802AD090[];
extern float lbl_8042DB70;
void fn_8003E9B4(Ent800AB3D8* e, Vec800AB3D8* v);

int fn_800AB3D8(int idx, Vec800AB3D8* out)
{
	float zero = lbl_8042DB70;
	out->z     = zero;
	out->x     = zero;
	out->y     = lbl_802AD0D0[idx]->f148;
	fn_8003E9B4(lbl_802AD090[idx], out);
	return 1;
}
}
