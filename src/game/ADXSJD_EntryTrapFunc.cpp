// Stores its argument(s) into the object at +0x48, +0x4c.

extern "C" {
struct ObjADXSJD_EntryTrapFunc {
	unsigned char pad0[0x48];
	int f48;
	int f4c;
};

void ADXSJD_EntryTrapFunc(ObjADXSJD_EntryTrapFunc* o, int a1, int a2)
{
	o->f48 = a1;
	o->f4c = a2;
}
}
