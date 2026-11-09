// Returns the int field at +0x18.

extern "C" {
struct ObjADXB_GetTotalNumSmpl {
	unsigned char pad[0x18];
	int f;
};

int ADXB_GetTotalNumSmpl(ObjADXB_GetTotalNumSmpl* o)
{
	return o->f;
}
}
