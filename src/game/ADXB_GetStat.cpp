// Returns the int field at +0x4.

extern "C" {
struct ObjADXB_GetStat {
	unsigned char pad[4];
	int f;
};

int ADXB_GetStat(ObjADXB_GetStat* o)
{
	return o->f;
}
}
