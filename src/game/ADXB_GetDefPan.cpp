// Returns the default pan of channel k (halfwords from +0xD2).

extern "C" {
struct Obj_ADXB_GetDefPan {
	unsigned char pad[0xd2];
	short s[1];
};

short ADXB_GetDefPan(Obj_ADXB_GetDefPan* o, int k)
{
	return o->s[k];
}
}
