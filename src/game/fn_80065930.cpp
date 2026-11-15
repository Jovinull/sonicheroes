// A PARTICLE_MATERIAL constructor or initialiser (HYPOTHESIS): it stores the PARTICLE_MATERIAL vtable that the
// named constructor also stores; which PS2 constructor it is stays unresolved.

// PARTICLE_MATERIAL-family constructor variant: installs the vtable at +0x54,
// initialises the flags/matrix fields, links the node into the global list at
// lbl_8042C2E0->0x28, then copies the info field into the shared target object
// depending on flags 0x10000 / 0x20000.

extern "C" {
extern unsigned char lbl_80243BF8[];
extern float lbl_8042D4A8;
extern float lbl_8042D4DC;
extern float lbl_8042D4E0;
extern float lbl_8042D4E4;

struct Tgt80065930 {
	unsigned char pad0[0xC];
	int fC;
	unsigned char pad10[0x1C];
	int f2C;
};

struct Node80065930 {
	unsigned short f0;
	unsigned char pad2[2];
	int f4;
	int f8;
	unsigned short fC;
	unsigned short fE;
	float f10;
	float f14;
	float f18;
	float f1C;
	unsigned char pad20[4];
	float f24;
	unsigned char pad28[4];
	Tgt80065930* f2C;
	unsigned int f30;
	void* f34;
	int f38;
	unsigned int f3C;
	unsigned int f40;
	Node80065930* f44;
	Node80065930* f48;
	unsigned int f4C;
	unsigned int f50;
	unsigned char* f54;
	float f58;
	float f5C;
	float f60;
	unsigned int f64;
	unsigned int f68;
	unsigned int f6C;
	float f70;
	float f74;
	float f78;
};

struct Owner80065930 {
	unsigned char pad0[0x28];
	Node80065930* f28;
};

extern Owner80065930* lbl_8042C2E0;

void fn_80065930(Node80065930* o, int flags, Tgt80065930* info)
{
	int value;
	Tgt80065930* p;
	int f;
	Node80065930* prev;

	o->f54    = lbl_80243BF8;
	o->f8     = 0;
	o->f4     = flags | 0x20000;
	o->fC     = 0;
	o->fE     = 0;
	float one = lbl_8042D4A8;
	o->f10    = one;
	o->f14    = one;
	o->f18    = lbl_8042D4DC;
	o->f1C    = lbl_8042D4E0;
	o->f24    = lbl_8042D4E4;
	o->f44    = 0;
	o->f48    = 0;
	o->f4C    = 0;
	o->f50    = 0;
	o->f34    = 0;
	o->f0     = 0;
	o->f3C    = 0;
	o->f40    = 0;
	o->f60    = one;
	o->f5C    = one;
	o->f58    = one;
	o->f78    = one;
	o->f74    = one;
	o->f70    = one;
	o->f6C    = 0;
	o->f68    = 0;
	o->f64    = 0;
	o->f30    = 0;
	o->f38    = 0;
	if (lbl_8042C2E0 == 0) {
		o->f8 = 0;
	} else if (o->f8 != 1) {
		prev = lbl_8042C2E0->f28;
		if (prev == 0) {
			lbl_8042C2E0->f28 = o;
			o->f48            = 0;
			o->f44            = 0;
		} else {
			while (prev->f48 != 0) {
				prev = prev->f48;
			}
			prev->f48 = o;
			o->f44    = prev;
			o->f48    = 0;
		}
		o->f8 = 1;
	}
	o->f2C = info;
	value  = info->f2C;
	p      = o->f2C;
	if (p != 0) {
		f = o->f4;
		if ((f & 0x10000) != 0) {
			p->fC  = value;
			o->f38 = value;
			return;
		}
		if ((f & 0x20000) != 0) {
			p->f2C = value;
			o->f38 = value;
		}
	}
}
}
