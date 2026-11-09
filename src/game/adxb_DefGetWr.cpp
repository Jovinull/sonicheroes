// Reports the default write window: start (+0x8C), room before the end (+0x40) and remaining input (+0x18 - +0x88); returns the buffer at +0x3C.

extern "C" {
struct Obj_adxb_DefGetWr {
	unsigned char pad[0x18];
	int f18;
	unsigned char pad1[0x1c];
	int f38;
	int f3c;
	int f40;
	unsigned char pad2[0x44];
	int f88;
	int f8c;
};

int adxb_DefGetWr(Obj_adxb_DefGetWr* o, int* a, int* b, int* c)
{
	*a = o->f8c;
	*b = o->f40 - o->f8c;
	*c = o->f18 - o->f88;
	return o->f3c;
}
}
