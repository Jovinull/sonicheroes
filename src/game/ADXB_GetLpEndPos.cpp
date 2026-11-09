// Returns the int field at +0x30.

extern "C" {
struct ObjADXB_GetLpEndPos {
	unsigned char pad[0x30];
	int f;
};

int ADXB_GetLpEndPos(ObjADXB_GetLpEndPos* o)
{
	return o->f;
}
}
