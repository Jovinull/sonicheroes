// Returns 1 when the object's vector dotted with lbl_803E7050 is below lbl_8042E254 and flag 0x8000 is clear.
struct V3_800E6F7C {
	float x;
	float y;
	float z;
};
struct Obj800E6F7C {
	unsigned char pad0[0xC];
	float fC;
	float f10;
	float f14;
	unsigned int f18;
};

extern "C" {
extern V3_800E6F7C lbl_803E7050;
extern float lbl_8042E254;

int fn_800E6F7C(Obj800E6F7C* o)
{
	if (o->f14 * lbl_803E7050.z + (o->fC * lbl_803E7050.x + o->f10 * lbl_803E7050.y)
	    >= lbl_8042E254) {
		return 0;
	}
	return (unsigned int)__cntlzw(o->f18 & 0x8000) >> 5;
}
}
