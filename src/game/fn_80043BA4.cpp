// Resets the player's action flags and timers to the idle mode 0x2B (clears the control bits in +0x6F6, zeroes the counters and the sub-block fields) and hands the sub-block to fn_800E12FC.
struct Sub80043BA4 {
	unsigned char pad0[0x10];
	short f10;
	unsigned char pad12[4];
	short f16;
	unsigned char pad18[0x78];
	int f90;
	unsigned char pad94[0x30];
	int fC4;
	unsigned char padC8[0x84];
	unsigned char f14C[2];
	short f14E;
	unsigned char pad150[8];
	short f158;
};
struct Obj80043BA4 {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[2];
	short f6F4;
	short f6F6;
	short f6F8;
	unsigned char pad6FA[0x66];
	Sub80043BA4 sub;
};

extern "C" {
void fn_800F1EB8(void* p, short v);
void fn_800E12FC(void* a, void* b);

void fn_80043BA4(Obj80043BA4* o)
{
	Sub80043BA4* s = &o->sub;
	short t;
	o->f6F6 = o->f6F6 & ~0x2504;
	o->f6F6 = o->f6F6 & 0xFFFFF0FF;
	o->f6F6 = o->f6F6 & 0xFFFF1FFF;
	t       = s->f10;
	s->f10  = t & 0xFFFF31FC;
	o->f6F8 = 0;
	s->f90  = 0;
	s->f16  = 0;
	s->fC4  = 0;
	fn_800F1EB8(s->f14C, t);
	s->f158 = s->f158 | 4;
	s->f14E = 0;
	o->f6F0 = 0x2B;
	o->f6F6 = o->f6F6 & 0xFFFFEFFF;
	o->f6F4 = 0;
	fn_800E12FC((char*)o + 0x720, s);
}
}
