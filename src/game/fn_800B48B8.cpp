// Resets all 43 slots and the pending state of the object.
struct Slot800B48B8 {
	unsigned char pad0[6];
	signed char f6;
	unsigned char pad7[5];
	int fC;
	unsigned char pad10[2];
	short f12;
	unsigned char pad14[0x20];
	int f34;
};
struct Obj800B48B8 {
	signed char f0;
	signed char f1;
	signed char f2;
	unsigned char pad3[0x96D];
	int f970;
	signed char f974;
	signed char f975;
};

extern "C" {
void fn_800B2110(Slot800B48B8* s);
void fn_8020AD44();
void fn_8020ADCC(int a);
void fn_8020AE38();

void fn_800B48B8(Obj800B48B8* o)
{
	signed char i;
	Slot800B48B8* p = (Slot800B48B8*)((char*)o + 8);
	for (i = 0; i < 0x2B; i++) {
		p->f12 = 0;
		p->f34 = 0;
		p->fC |= 4;
		if (o->f0 != 0) {
			p->f6 = -0x80;
		}
		fn_800B2110(p);
		p++;
	}
	o->f1 = 0;
	o->f2 = 0x26;
	if (o->f970 != 0) {
		fn_8020AD44();
		fn_8020ADCC(2);
		o->f974 = 0;
		o->f975 = 0;
		o->f970 = 0;
	}
	fn_8020AE38();
	o->f0 = 0;
}
}
