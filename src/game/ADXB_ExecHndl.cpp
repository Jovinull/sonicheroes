// Dispatches one decode step on the stream format at +0x98 (0 ADX, 10 AHX, 2 SPSD, 3 AIFF, 4 AU, 1 WAV).

extern "C" {
struct Obj_ADXB_ExecHndl {
	unsigned char pad[0x98];
	short s98;
};
void ADXB_ExecOneAdx(void*);
void ADXB_ExecOneAhx(void*);
void ADXB_ExecOneSpsd(void*);
void ADXB_ExecOneAiff(void*);
void ADXB_ExecOneAu(void*);
void ADXB_ExecOneWav(void*);

void ADXB_ExecHndl(Obj_ADXB_ExecHndl* o)
{
	short t = o->s98;
	if (t == 0) {
		ADXB_ExecOneAdx(o);
	} else if (t == 10) {
		ADXB_ExecOneAhx(o);
	} else if (t == 2) {
		ADXB_ExecOneSpsd(o);
	} else if (t == 3) {
		ADXB_ExecOneAiff(o);
	} else if (t == 4) {
		ADXB_ExecOneAu(o);
	} else if (t == 1) {
		ADXB_ExecOneWav(o);
	}
}
}
