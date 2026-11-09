// Counts how many of the seven handle fields (0x54, 0x60, 0x6C, 0x78, 0x84, 0x90, 0x9C) are set.

extern "C" {
struct Obj80116AE4 {
	unsigned char pad[0x54];
	unsigned f54;
	unsigned char pad1[0x60 - 0x58];
	unsigned f60;
	unsigned char pad2[0x6c - 0x64];
	unsigned f6c;
	unsigned char pad3[0x78 - 0x70];
	unsigned f78;
	unsigned char pad4[0x84 - 0x7c];
	unsigned f84;
	unsigned char pad5[0x90 - 0x88];
	unsigned f90;
	unsigned char pad6[0x9c - 0x94];
	unsigned f9c;
};

int fn_80116AE4(Obj80116AE4* o)
{
	int n = 0;
	if (o->f54 != 0) {
		n = 1;
	}
	if (o->f60 != 0) {
		n += 1;
	}
	if (o->f6c != 0) {
		n += 1;
	}
	if (o->f78 != 0) {
		n += 1;
	}
	if (o->f84 != 0) {
		n += 1;
	}
	if (o->f90 != 0) {
		n += 1;
	}
	if (o->f9c != 0) {
		n += 1;
	}
	return n;
}
}
