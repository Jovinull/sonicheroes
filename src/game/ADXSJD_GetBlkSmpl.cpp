// Forwards to ADXB_GetBlkSmpl with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetBlkSmpl {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetBlkSmpl(int);

int ADXSJD_GetBlkSmpl(ObjADXSJD_GetBlkSmpl* o)
{
	return ADXB_GetBlkSmpl(o->f4);
}
}
