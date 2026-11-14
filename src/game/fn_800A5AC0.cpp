// Copies the vector at +0x140, subtracts the vector at +0x1CC, zeroes Y and
// returns the length of the resulting vector.
struct Blk800A5AC0 {
	unsigned char b[12];
};
struct V3_800A5AC0 {
	float x;
	float y;
	float z;
};
struct Obj800A5AC0 {
	unsigned char pad0[0x140];
	V3_800A5AC0 v140;
	unsigned char pad14C[0x80];
	V3_800A5AC0 v1CC;
};

extern "C" {
extern float lbl_8042DA74;
float fn_801991B4(V3_800A5AC0* a);

float fn_800A5AC0(Obj800A5AC0* o)
{
	V3_800A5AC0 sp;
	*(Blk800A5AC0*)&sp = *(Blk800A5AC0*)&o->v140;
	sp.x               = sp.x - o->v1CC.x;
	sp.y               = sp.y - o->v1CC.y;
	sp.z               = sp.z - o->v1CC.z;
	sp.y               = lbl_8042DA74;
	return fn_801991B4(&sp);
}
}
