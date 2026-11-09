// Moves from state 0 to state 1.

extern "C" {
struct Obj_ADXB_Start {
	unsigned char pad[4];
	int f4;
};

void ADXB_Start(Obj_ADXB_Start* o)
{
	if (o->f4 == 0) {
		o->f4 = 1;
	}
}
}
