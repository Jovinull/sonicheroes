// Returns 1 when the registered handle of the given id is held by one of the object's active slots.
struct Obj80091F54 {
	unsigned char pad0[0x39];
	signed char f39;
	unsigned char pad3A[0xFA];
	unsigned int f134[1];
};

extern "C" {
extern unsigned int lbl_802AD070[];

int fn_80091F54(Obj80091F54* o, int id)
{
	int i;
	unsigned int t = lbl_802AD070[id];
	if (t == 0) {
		return 0;
	}
	for (i = 0; i < o->f39; i++) {
		if (t == o->f134[i]) {
			return 1;
		}
	}
	return 0;
}
}
