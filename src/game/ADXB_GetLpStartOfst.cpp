// Returns the loop start offset at +0x2C, or 0 for a null handle.

extern "C" {
struct Obj_ADXB_GetLpStartOfst {
	unsigned char pad[0x2c];
	int f2c;
};

int ADXB_GetLpStartOfst(Obj_ADXB_GetLpStartOfst* o)
{
	if (o == 0) {
		return 0;
	}
	return o->f2c;
}
}
