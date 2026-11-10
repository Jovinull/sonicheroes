// Initialises the entry: stores the index, the two table bytes of that index and clears the counters.
struct Pair80115478 {
	unsigned char a;
	unsigned char b;
};
struct Obj80115478 {
	unsigned char pad0[0x28];
	int f28;
	int f2C;
	unsigned char f30;
	unsigned char f31;
	unsigned char pad32[2];
	int f34;
	int f38;
	int f3C;
	float f40;
};

extern "C" {
extern Pair80115478 lbl_80288DF0[];
extern float lbl_8042EA20;

void fn_80115478(Obj80115478* o, int i)
{
	o->f28 = i;
	o->f30 = lbl_80288DF0[i].a;
	o->f31 = lbl_80288DF0[i].b;
	o->f2C = 0;
	o->f34 = 0;
	o->f38 = 0;
	o->f3C = 0;
	o->f40 = lbl_8042EA20;
}
}
