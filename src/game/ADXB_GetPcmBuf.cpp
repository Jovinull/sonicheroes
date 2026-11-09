// Returns the int field at +0x3c.

extern "C" {
struct ObjADXB_GetPcmBuf {
	unsigned char pad[0x3c];
	int f;
};

int ADXB_GetPcmBuf(ObjADXB_GetPcmBuf* o)
{
	return o->f;
}
}
