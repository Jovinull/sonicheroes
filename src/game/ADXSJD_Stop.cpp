// Stops the decoder (ADXB_Stop on the handle at +4) and sets the state byte at +1 to 0.

extern "C" {
struct Obj_ADXSJD_Stop {
	unsigned char pad0;
	signed char c1;
	unsigned char pad2[2];
	int f4;
};
void ADXB_Stop(int);

void ADXSJD_Stop(Obj_ADXSJD_Stop* o)
{
	ADXB_Stop(o->f4);
	o->c1 = 0;
}
}
