// Returns 1 when the projected value does not exceed lbl_8042D3FC, bit 0x8000 of the flags is clear and bit 2 is clear.
struct V3_800574AC {
	float x;
	float y;
	float z;
};
struct Obj800574AC {
	unsigned char pad0[0xC];
	float fC;
	float f10;
	float f14;
	unsigned int f18;
};

extern "C" {
extern V3_800574AC lbl_802D6350;
extern float lbl_8042D3FC;

int fn_800574AC(Obj800574AC* o)
{
	unsigned int fl;
	if (o->f14 * lbl_802D6350.z + (o->fC * lbl_802D6350.x + o->f10 * lbl_802D6350.y)
	    > lbl_8042D3FC) {
		return 0;
	}
	fl = o->f18;
	if ((fl & 0x8000) != 0) {
		return 0;
	}
	return (unsigned int)__cntlzw(fl & 2) >> 5;
}
}
