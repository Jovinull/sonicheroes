// Returns the int field at +0x10.

extern "C" {
struct ObjADXB_GetBlkSmpl {
	unsigned char pad[0x10];
	int f;
};

int ADXB_GetBlkSmpl(ObjADXB_GetBlkSmpl* o)
{
	return o->f;
}
}
