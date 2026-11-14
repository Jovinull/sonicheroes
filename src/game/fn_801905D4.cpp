// Unless either pointer is null, stores the byte and the two doubles into the object at 0xDC,
// 0xE0 and 0xE8 and sets flag 0x4000 of its word at 0x08.
struct Obj801905D4 {
	unsigned char pad0[0x8];
	unsigned int flags; // 0x08
	unsigned char padC[0xDC - 0xC];
	unsigned char fDC;
	unsigned char padDD[0x3];
	double fE0;
	double fE8;
};

extern "C" {
void fn_801905D4(void* owner, Obj801905D4* o, unsigned char b, double x, double y)
{
	if (owner == 0 || o == 0) {
		return;
	}
	o->fDC = b;
	o->fE0 = x;
	o->fE8 = y;
	o->flags |= 0x4000;
}
}
