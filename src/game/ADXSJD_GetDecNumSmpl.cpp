// Returns the int field at +0x2c.

extern "C" {
struct ObjADXSJD_GetDecNumSmpl {
	unsigned char pad[0x2c];
	int f;
};

int ADXSJD_GetDecNumSmpl(ObjADXSJD_GetDecNumSmpl* o)
{
	return o->f;
}
}
