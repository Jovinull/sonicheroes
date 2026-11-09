// Returns the int field at +0x94.

extern "C" {
struct ObjADXB_GetDecDtLen {
	unsigned char pad[0x94];
	int f;
};

int ADXB_GetDecDtLen(ObjADXB_GetDecDtLen* o)
{
	return o->f;
}
}
