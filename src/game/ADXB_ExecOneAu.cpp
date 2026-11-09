// Dispatches the AU decode step on the sample format at +0x9A (2 -> u-law, 1 -> 8-bit, else 16-bit).

extern "C" {
struct Obj_ADXB_ExecOneAu {
	unsigned char pad[0x9a];
	short s9a;
};
void ADXB_ExecOneAu16(void*);
void ADXB_ExecOneAu8(void*);
void ADXB_ExecOneAuUlaw(void*);

void ADXB_ExecOneAu(Obj_ADXB_ExecOneAu* o)
{
	short t = o->s9a;
	if (t == 2) {
		ADXB_ExecOneAuUlaw(o);
		return;
	}
	if (t == 1) {
		ADXB_ExecOneAu8(o);
		return;
	}
	ADXB_ExecOneAu16(o);
}
}
