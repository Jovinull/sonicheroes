// Forwards to ADXB_GetTotalNumSmpl with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetTotalNumSmpl {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetTotalNumSmpl(int);

int ADXSJD_GetTotalNumSmpl(ObjADXSJD_GetTotalNumSmpl* o)
{
	return ADXB_GetTotalNumSmpl(o->f4);
}
}
