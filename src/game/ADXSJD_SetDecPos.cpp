// Stores its argument(s) into the object at +0x34.

extern "C" {
struct ObjADXSJD_SetDecPos {
	unsigned char pad0[0x34];
	int f34;
};

void ADXSJD_SetDecPos(ObjADXSJD_SetDecPos* o, int a1)
{
	o->f34 = a1;
}
}
