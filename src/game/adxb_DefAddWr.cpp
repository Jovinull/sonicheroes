// Advances the default write cursors at +0x8C and +0x88 by arg2.

extern "C" {
struct Obj_adxb_DefAddWr {
	unsigned char pad[0x88];
	int f88;
	int f8c;
};

void adxb_DefAddWr(Obj_adxb_DefAddWr* o, int u, int a)
{
	o->f8c = o->f8c + a;
	o->f88 = o->f88 + a;
}
}
