// Returns the int field at +0x90.

extern "C" {
struct ObjADXB_GetDecNumSmpl {
	unsigned char pad[0x90];
	int f;
};

int ADXB_GetDecNumSmpl(ObjADXB_GetDecNumSmpl* o)
{
	return o->f;
}
}
