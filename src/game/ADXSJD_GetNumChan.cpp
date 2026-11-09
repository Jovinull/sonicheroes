// Forwards to ADXB_GetNumChan with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetNumChan {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetNumChan(int);

int ADXSJD_GetNumChan(ObjADXSJD_GetNumChan* o)
{
	return ADXB_GetNumChan(o->f4);
}
}
