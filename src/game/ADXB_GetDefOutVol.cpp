// Returns the short field at +0xd0.

extern "C" {
struct ObjADXB_GetDefOutVol {
	unsigned char pad[0xd0];
	short f;
};

short ADXB_GetDefOutVol(ObjADXB_GetDefOutVol* o)
{
	return o->f;
}
}
