// Dispatches the WAV decode step on the sample width at +0x9A (2 -> 4-bit, 1 -> 8-bit, 0 -> 16-bit).

extern "C" {
struct Obj_ADXB_ExecOneWav {
	unsigned char pad[0x9a];
	short s9a;
};
void ADXB_ExecOneWav16(void*);
void ADXB_ExecOneWav4(void*);
void ADXB_ExecOneWav8(void*);

void ADXB_ExecOneWav(Obj_ADXB_ExecOneWav* o)
{
	short t = o->s9a;
	if (t == 2) {
		ADXB_ExecOneWav4(o);
	} else if (t == 1) {
		ADXB_ExecOneWav8(o);
	} else if (t == 0) {
		ADXB_ExecOneWav16(o);
	}
}
}
