// Returns the signed status byte at +1.

extern "C" {
struct ObjADXSJD_GetStat {
	unsigned char pad[1];
	signed char stat;
};

int ADXSJD_GetStat(ObjADXSJD_GetStat* o)
{
	return o->stat;
}
}
