// Forwards to ADXB_GetOutBps with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetOutBps {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetOutBps(int);

int ADXSJD_GetOutBps(ObjADXSJD_GetOutBps* o)
{
	return ADXB_GetOutBps(o->f4);
}
}
