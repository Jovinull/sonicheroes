// Forwards to ADXB_GetLpEndPos with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetLpEndPos {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetLpEndPos(int);

int ADXSJD_GetLpEndPos(ObjADXSJD_GetLpEndPos* o)
{
	return ADXB_GetLpEndPos(o->f4);
}
}
