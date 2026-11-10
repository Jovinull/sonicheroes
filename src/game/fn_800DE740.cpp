// Returns 1 when the object's vector dotted with lbl_803E7028 is below lbl_8042E1C8 and its dot with lbl_80242B38 lies strictly between lbl_8042E1CC and lbl_8042E1D0.
struct V3_800DE740 {
	float x;
	float y;
	float z;
};
struct Obj800DE740 {
	unsigned char pad0[0xC];
	float fC;
	float f10;
	float f14;
};

extern "C" {
extern V3_800DE740 lbl_80242B38;
extern V3_800DE740 lbl_803E7028;
extern float lbl_8042E1C8;
extern float lbl_8042E1CC;
extern float lbl_8042E1D0;

int fn_800DE740(Obj800DE740* o)
{
	float d;
	if (o->f14 * lbl_803E7028.z + (o->fC * lbl_803E7028.x + o->f10 * lbl_803E7028.y)
	    >= lbl_8042E1C8) {
		return 0;
	}
	d = o->f14 * lbl_80242B38.z + (o->fC * lbl_80242B38.x + o->f10 * lbl_80242B38.y);
	if (d <= lbl_8042E1CC) {
		return 0;
	}
	return (unsigned int)__cntlzw(d >= lbl_8042E1D0) >> 5;
}
}
