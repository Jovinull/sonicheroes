// Forwards to ADXB_GetLpEndOfst with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetLpEndOfst {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetLpEndOfst(int);

int ADXSJD_GetLpEndOfst(ObjADXSJD_GetLpEndOfst* o)
{
	return ADXB_GetLpEndOfst(o->f4);
}
}
