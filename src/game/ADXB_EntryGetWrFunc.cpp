// Stores its argument(s) into the object at +0x78, +0x7c.

extern "C" {
struct ObjADXB_EntryGetWrFunc {
	unsigned char pad0[0x78];
	int f78;
	int f7c;
};

void ADXB_EntryGetWrFunc(ObjADXB_EntryGetWrFunc* o, int a1, int a2)
{
	o->f78 = a1;
	o->f7c = a2;
}
}
