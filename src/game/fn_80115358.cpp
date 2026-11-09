// If word 0x28 equals v, sets words 0x2C and 0x4C to -1.

extern "C" {
struct Obj80115358 {
	unsigned char pad[0x28];
	int f28;
	int f2c;
	unsigned char pad1[0x4c - 0x30];
	int f4c;
};

void fn_80115358(Obj80115358* o, int v)
{
	if (o->f28 == v) {
		o->f2c = -1;
		o->f4c = -1;
	}
}
}
