// Forwards to ADXB_GetLpStartPos with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetLpStartPos {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetLpStartPos(int);

int ADXSJD_GetLpStartPos(ObjADXSJD_GetLpStartPos* o)
{
	return ADXB_GetLpStartPos(o->f4);
}
}
