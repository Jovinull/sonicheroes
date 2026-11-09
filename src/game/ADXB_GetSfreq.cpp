// Returns the int field at +0x14.

extern "C" {
struct ObjADXB_GetSfreq {
	unsigned char pad[0x14];
	int f;
};

int ADXB_GetSfreq(ObjADXB_GetSfreq* o)
{
	return o->f;
}
}
