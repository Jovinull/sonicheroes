// Returns the int field at +0x28.

extern "C" {
struct ObjADXB_GetLpStartPos {
	unsigned char pad[0x28];
	int f;
};

int ADXB_GetLpStartPos(ObjADXB_GetLpStartPos* o)
{
	return o->f;
}
}
