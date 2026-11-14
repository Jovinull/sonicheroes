// Starts a fade on an object unless one is running (flag 0x4 of the halfword at 0xA4): clears
// flags 0x1/0x8 and sets 0x4. Speed 0 instead sets flag 0x1 of the halfword at 0x04 and returns 0;
// speed -1 resets the step state; any other speed also stores the step 0xFF / speed (1 above 0xFF)
// and sets flag 0x2. Returns 1 when started, 0 otherwise. Names are inferred.
struct Obj8005FD8C {
	unsigned char pad0[0x4];
	unsigned short f4;
	unsigned char pad6[0xA4 - 0x6];
	unsigned short flags; // 0xA4
	unsigned char fA6;
	unsigned char padA7;
	unsigned short fA8;
	unsigned char step; // 0xAA
};

extern "C" {
int fn_8005FD8C(Obj8005FD8C* o, short speed)
{
	if (o->flags & 4) {
		return 0;
	}
	o->flags &= ~1;
	o->flags &= ~8;
	o->flags |= 4;
	switch (speed) {
		case 0:
			o->f4 |= 1;
			return 0;
		case -1:
			o->fA6 = 0;
			o->fA8 = 0;
			break;
		default:
			o->fA6 = 0;
			o->fA8 = 0;
			if (speed > 0xFF) {
				o->step = 1;
			} else {
				o->step = 0xFF / speed;
			}
			o->flags |= 2;
			break;
	}
	return 1;
}
}
