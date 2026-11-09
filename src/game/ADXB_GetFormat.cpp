// Returns the short field at +0x98.

extern "C" {
struct ObjADXB_GetFormat {
	unsigned char pad[0x98];
	short f;
};

short ADXB_GetFormat(ObjADXB_GetFormat* o)
{
	return o->f;
}
}
