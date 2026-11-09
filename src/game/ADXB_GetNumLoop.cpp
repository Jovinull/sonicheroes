// Returns the short field at +0x24.

extern "C" {
struct ObjADXB_GetNumLoop {
	unsigned char pad[0x24];
	short f;
};

short ADXB_GetNumLoop(ObjADXB_GetNumLoop* o)
{
	return o->f;
}
}
