// Returns ADXB_GetLpStartOfst of the decoder handle at +4, or 0 for a null object.

extern "C" {
struct ObjADXSJD_GetLpStartOfst {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetLpStartOfst(int);

int ADXSJD_GetLpStartOfst(ObjADXSJD_GetLpStartOfst* o)
{
	if (o == 0) {
		return 0;
	}
	return ADXB_GetLpStartOfst(o->f4);
}
}
