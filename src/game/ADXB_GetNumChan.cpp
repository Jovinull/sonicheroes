// Returns the signed char field at +0xE.

extern "C" {
struct ObjADXB_GetNumChan {
	unsigned char pad[0xE];
	signed char f;
};

int ADXB_GetNumChan(ObjADXB_GetNumChan* o)
{
	return o->f;
}
}
