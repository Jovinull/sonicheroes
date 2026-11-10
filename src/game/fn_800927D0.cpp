// Returns the index of the slot whose entry has the given secondary id (-1 when none).
struct Ent800927D0 {
	unsigned char pad0[0x9B0];
	int f9B0;
};
struct Obj800927D0 {
	unsigned char pad0[0x39];
	signed char f39;
	unsigned char pad3A[0xDA];
	Ent800927D0* f114[1];
};

extern "C" {
int fn_800927D0(Obj800927D0* o, int id)
{
	int i;
	for (i = 0; i < o->f39; i++) {
		if (o->f114[i]->f9B0 == id) {
			return i;
		}
	}
	return -1;
}
}
