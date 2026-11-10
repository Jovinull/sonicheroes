// Returns the index of the slot whose entry has the given id (-1 when none).
struct Ent8009278C {
	unsigned char pad0[0x9B4];
	int f9B4;
};
struct Obj8009278C {
	unsigned char pad0[0x39];
	signed char f39;
	unsigned char pad3A[0xDA];
	Ent8009278C* f114[1];
};

extern "C" {
int fn_8009278C(Obj8009278C* o, int id)
{
	int i;
	for (i = 0; i < o->f39; i++) {
		if (o->f114[i]->f9B4 == id) {
			return i;
		}
	}
	return -1;
}
}
