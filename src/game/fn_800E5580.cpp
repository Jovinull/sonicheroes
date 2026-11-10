// Returns 1 when flag 0x8000 is clear and the object's vector dotted with lbl_803E705C is below lbl_8042E288.
struct V3_800E5580 {
	float x;
	float y;
	float z;
};
struct Obj800E5580 {
	unsigned char pad0[0xC];
	float fC;
	float f10;
	float f14;
	unsigned int f18;
};

extern "C" {
extern V3_800E5580 lbl_803E705C;
extern float lbl_8042E288;

int fn_800E5580(Obj800E5580* o)
{
	if ((o->f18 & 0x8000) != 0) {
		return 0;
	}
	return (unsigned int)__cntlzw(
	           (o->f14 * lbl_803E705C.z + (o->fC * lbl_803E705C.x + o->f10 * lbl_803E705C.y))
	           >= lbl_8042E288)
	    >> 5;
}
}
