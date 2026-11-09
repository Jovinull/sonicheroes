// Returns the int field at +0xbc.

extern "C" {
struct ObjADXB_GetAinfLen {
	unsigned char pad[0xbc];
	int f;
};

int ADXB_GetAinfLen(ObjADXB_GetAinfLen* o)
{
	return o->f;
}
}
