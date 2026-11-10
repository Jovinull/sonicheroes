// Copies an optional float triple into +0x58 and an optional word triple into +0x64.
struct Obj800A1FD0 {
	unsigned char pad0[0x58];
	float f58;
	float f5C;
	float f60;
	int f64;
	int f68;
	int f6C;
};
struct F3 {
	float x;
	float y;
	float z;
};
struct I3 {
	int x;
	int y;
	int z;
};

extern "C" {
void fn_800A1FD0(Obj800A1FD0* o, F3* a, I3* b)
{
	if (a != 0) {
		o->f58 = a->x;
		o->f5C = a->y;
		o->f60 = a->z;
	}
	if (b != 0) {
		o->f64 = b->x;
		o->f68 = b->y;
		o->f6C = b->z;
	}
}
}
