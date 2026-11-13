extern "C" {
struct ObjADXB_DecodeHeaderAiff {
	unsigned char pad0[2];
	short f2;
	unsigned char pad4[8];
	signed char fC;
	signed char fD;
	signed char fE;
	signed char fF;
	int f10;
	int f14;
	int f18;
	short f1C;
	unsigned char pad1E[2];
	int f20;
	short f24;
	short f26;
	int f28;
	int f2C;
	int f30;
	int f34;
	unsigned char pad38[4];
	int f3C;
	int f40;
	int f44;
	unsigned char pad48[8];
	int f50;
	int f54;
	int f58;
	int f5C;
	int f60;
	int f64;
	unsigned char pad68[0x20];
	int f88;
	int f8C;
	unsigned char pad90[8];
	short f98;
	short f9A;
};

unsigned int AIFF_GetInfo(int a, int* b, int* c, int* d, int* e);

int ADXB_DecodeHeaderAiff(ObjADXB_DecodeHeaderAiff* o, int a, int b)
{
	int sp14;
	int sp10;
	int spC;
	int sp8;
	short len;
	int err;
	unsigned int ret;

	o->f2 = 1;
	if (b < 0x1000) {
		len = 0;
		err = -1;
	} else {
		ret = AIFF_GetInfo(a, &sp8, &spC, &sp10, &sp14);
		if (ret == 0) {
			err = -1;
		} else {
			len = (short)(ret - a);
			if (len <= 0) {
				err = -1;
			} else {
				err    = 0;
				o->f14 = sp8;
				o->fE  = (unsigned char)spC;
				o->fD  = (unsigned char)sp10;
				o->f18 = sp14;
				o->fC  = -1;
				o->fF  = o->fE * (signed char)o->fD / 8;
				o->f10 = 1;
			}
		}
	}
	if (err < 0) {
		return 0;
	}
	o->f1C = 0;
	o->f26 = 0;
	o->f24 = 0;
	o->f34 = 0;
	o->f30 = 0;
	o->f2C = 0;
	o->f28 = 0;
	o->f20 = 0;
	o->f50 = o->fE;
	o->f54 = o->fF;
	o->f58 = o->f10;
	o->f5C = o->f3C;
	o->f60 = o->f40;
	o->f64 = o->f44;
	o->f8C = 0;
	o->f88 = 0;
	o->f98 = 3;
	if (o->fD == 8) {
		o->f9A = 1;
	} else {
		o->f9A = 0;
	}
	return len;
}
}
