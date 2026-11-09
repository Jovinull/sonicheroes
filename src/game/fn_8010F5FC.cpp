// One-shot reset: when the flag at 0x1A8 is clear, drops bit 0x10 from the flags of the object at 0x70, sets 0x120/0x11C, clears the 0x80-byte buffer at 0x124 and raises the flag.

extern "C" {
struct Flags8010F5FC {
	unsigned char pad[4];
	unsigned f4;
};
struct Obj8010F5FC {
	unsigned char pad[0x70];
	Flags8010F5FC* f70;
	unsigned char pad1[0x11c - 0x74];
	int f11c;
	int f120;
	unsigned char buf[0x84];
	int f1a8;
};
void* memset(void*, int, unsigned);

void fn_8010F5FC(Obj8010F5FC* o)
{
	if (o->f1a8 == 0) {
		Flags8010F5FC* y = o->f70;
		if (y != 0) {
			y->f4 = y->f4 & ~0x10;
		}
		o->f120 = 1;
		o->f11c = 0;
		memset(o->buf, 0, 0x80);
		o->f1a8 = 1;
	}
}
}
