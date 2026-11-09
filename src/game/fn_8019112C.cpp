// Sets flag 0x8000 at +0x30 and the id (u8 arg1) at +0xEE, sets or clears flag 0x80 at +0x2C by arg2 == 1, and adjusts the state byte at +0xEB from the states at +0xE6/+0xE7.

extern "C" {
struct Obj8019112C {
	unsigned char pad[0x2c];
	unsigned f2c;
	unsigned f30;
	unsigned char pad1[0xe6 - 0x34];
	unsigned char ce6;
	unsigned char ce7;
	unsigned char pad2[3];
	unsigned char ceb;
	unsigned char pad3[2];
	short cee;
};

void fn_8019112C(Obj8019112C* o, unsigned char k, int m)
{
	o->f30 |= 0x8000;
	o->cee = k;
	if (m == 1) {
		o->f2c |= 0x80;
	} else {
		o->f2c &= ~0x80;
	}
	if (o->ce6 == 2) {
		o->ceb = 4;
	}
	if (o->ce6 == 0 && o->ce7 >= 8) {
		o->ceb = 2;
	}
}
}
