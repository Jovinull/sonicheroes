// Stores its argument(s) into the object at +0x3c.

extern "C" {
struct ObjADXSJD_SetTrapNumSmpl {
	unsigned char pad0[0x3c];
	int f3c;
};

void ADXSJD_SetTrapNumSmpl(ObjADXSJD_SetTrapNumSmpl* o, int a1)
{
	o->f3c = a1;
}
}
