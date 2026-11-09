// When in state 3, resets the ADXPD decoder (handle at +8), clears +0x8C and returns to state 0.

extern "C" {
struct Obj_ADXB_Reset {
	unsigned char pad[4];
	int f4;
	int f8;
	unsigned char pad1[0x80];
	int f8c;
};
void ADXPD_Reset(int);

void ADXB_Reset(Obj_ADXB_Reset* o)
{
	if (o->f4 == 3) {
		ADXPD_Reset(o->f8);
		o->f8c = 0;
		o->f4  = 0;
	}
}
}
