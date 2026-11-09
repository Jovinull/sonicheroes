// Resets the decode counters (+0x2C..0x44, +0x98), sets the limit to 0x7FFFFFFF / -1, clears the flag at +3 and enters state 1.

extern "C" {
struct Obj_ADXSJD_Start {
	unsigned char pad[1];
	signed char c1;
	unsigned char pad2;
	signed char c3;
	int f4;
	unsigned char pad4[0x24];
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	unsigned char pad5[0x50];
	int f98;
};

void ADXSJD_Start(Obj_ADXSJD_Start* o)
{
	o->f98 = 0;
	o->f2c = 0;
	o->f30 = 0;
	o->f34 = 0;
	o->f38 = 0x7fffffff;
	o->f3c = -1;
	o->f40 = 0;
	o->f44 = 0;
	o->c3  = 0;
	o->c1  = 1;
}
}
