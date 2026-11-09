// Forwards to ADXB_GetNumLoop with the decoder handle at +4.

extern "C" {
struct ObjADXSJD_GetNumLoop {
	unsigned char pad[4];
	int f4;
};
int ADXB_GetNumLoop(int);

int ADXSJD_GetNumLoop(ObjADXSJD_GetNumLoop* o)
{
	return ADXB_GetNumLoop(o->f4);
}
}
