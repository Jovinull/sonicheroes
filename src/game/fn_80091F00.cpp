// Returns 1 when one of the object's active slots holds the given id.
struct Obj80091F00 {
	unsigned char pad0[0x39];
	signed char f39;
	unsigned char pad3A[0xD6];
	signed char f110[0x15];
	signed char f125[1];
};

extern "C" {
int fn_80091F00(Obj80091F00* o, int id)
{
	int i;
	for (i = 0; i < o->f39; i++) {
		if (o->f125[i] != 0 && o->f110[i] == id) {
			return 1;
		}
	}
	return 0;
}
}
