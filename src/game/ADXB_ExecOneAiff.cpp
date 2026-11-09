// Dispatches the AIFF decode step: 8-bit when the width at +0x9A is 1, else 16-bit.

extern "C" {
struct Obj_ADXB_ExecOneAiff {
	unsigned char pad[0x9a];
	short s9a;
};
void ADXB_ExecOneAiff16(void*);
void ADXB_ExecOneAiff8(void*);

void ADXB_ExecOneAiff(Obj_ADXB_ExecOneAiff* o)
{
	if (o->s9a == 1) {
		ADXB_ExecOneAiff8(o);
		return;
	}
	ADXB_ExecOneAiff16(o);
}
}
