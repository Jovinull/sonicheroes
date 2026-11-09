// Stores its argument(s) into the object at +0x44.

extern "C" {
struct ObjADXSJD_SetTrapDtLen {
	unsigned char pad0[0x44];
	int f44;
};

void ADXSJD_SetTrapDtLen(ObjADXSJD_SetTrapDtLen* o, int a1)
{
	o->f44 = a1;
}
}
