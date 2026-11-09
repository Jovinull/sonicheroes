// Returns the int field at +0x34.

extern "C" {
struct ObjADXB_GetLpEndOfst {
	unsigned char pad[0x34];
	int f;
};

int ADXB_GetLpEndOfst(ObjADXB_GetLpEndOfst* o)
{
	return o->f;
}
}
