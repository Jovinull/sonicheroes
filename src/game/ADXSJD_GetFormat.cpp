// Forwards to ADXB_GetFormat with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetFormat {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetFormat(int);

int ADXSJD_GetFormat(ObjADXSJD_GetFormat* o)
{
	return ADXB_GetFormat(o->f4);
}
}
