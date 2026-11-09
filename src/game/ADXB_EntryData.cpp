// Registers the input data (+0x48) and derives the frame count (+0x4C) from the byte count and the per-frame size (+0xF for ADX, else (+0xD / 8) * +0xE); resets the cursors.

extern "C" {
struct Obj_ADXB_EntryData {
	unsigned char pad[0xd];
	signed char cd;
	signed char ce;
	signed char cf;
	unsigned char pad1[0x38];
	int f48;
	int f4c;
	unsigned char pad2[0x24];
	int f74;
	unsigned char pad3[0x18];
	int f90;
	int f94;
	short s98;
};

void ADXB_EntryData(Obj_ADXB_EntryData* o, int a, int b)
{
	if (o->s98 == 0) {
		o->f48 = a;
		o->f4c = b / o->cf;
		o->f74 = 0;
		o->f90 = 0;
		o->f94 = 0;
		return;
	}
	o->f48 = a;
	o->f4c = b / ((o->cd / 8) * o->ce);
	o->f74 = 0;
	o->f90 = 0;
	o->f94 = 0;
}
}
