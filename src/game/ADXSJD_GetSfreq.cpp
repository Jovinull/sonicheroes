// Forwards to ADXB_GetSfreq with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetSfreq {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetSfreq(int);

int ADXSJD_GetSfreq(ObjADXSJD_GetSfreq* o)
{
	return ADXB_GetSfreq(o->f4);
}
}
