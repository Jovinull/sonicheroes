// Decodes a WAV header into the ADXB handle and returns the sample format.

extern "C" {
struct ObjADXB_DecodeHeaderWav {
	unsigned char pad0[2];
	short f2;
	unsigned char pad4[8];
	unsigned char fC;
	unsigned char fD;
	signed char fE;
	signed char fF;
	int f10;
	unsigned char pad14[8];
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
};

int ADX_DecodeInfoWav(
    int a, int b, short* c, void* d, void* e, void* f, void* g, void* h, void* i, void* j, void* k);

short ADXB_DecodeHeaderWav(ObjADXB_DecodeHeaderWav* o, int a, int b)
{
	short fmt;
	o->f2 = 1;
	if (ADX_DecodeInfoWav(a, b, &fmt, &o->fC, &o->fD, &o->fF, &o->fE, (char*)o + 0x14,
	        (char*)o + 0x18, &o->f10, (char*)o + 0x9A)
	    < 0) {
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
	o->f98 = 1;
	return fmt;
}
}
