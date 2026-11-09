// Initialises the seven-word record: 0, 0x40000000, 0x80000000 and four zeros.

extern "C" {
struct Rec80169508 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
};

void fn_80169508(Rec80169508* o)
{
	o->f0  = 0;
	o->f4  = 0x40000000;
	o->f8  = 0x80000000;
	o->fc  = 0;
	o->f10 = 0;
	o->f14 = 0;
	o->f18 = 0;
}
}
