// Stops the ADXPD decoder (handle at +8) and returns to state 0.

extern "C" {
struct Obj_ADXB_Stop {
	unsigned char pad[4];
	int f4;
	int f8;
};
void ADXPD_Stop(int);

void ADXB_Stop(Obj_ADXB_Stop* o)
{
	ADXPD_Stop(o->f8);
	o->f4 = 0;
}
}
