// Stores its argument(s) into the object at +0x40.

extern "C" {
struct ObjADXSJD_SetTrapCnt {
	unsigned char pad0[0x40];
	int f40;
};

void ADXSJD_SetTrapCnt(ObjADXSJD_SetTrapCnt* o, int a1)
{
	o->f40 = a1;
}
}
