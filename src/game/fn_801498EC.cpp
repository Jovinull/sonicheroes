// Finds the slot of kind 2, bumps the object's reference count, releases the slot's previous object,
// stores the new one and returns the owner.
extern "C" {
struct Slot801498EC {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;
void fn_801A491C(int p);

static inline Slot801498EC* FindSlot801498EC(int owner, int kind)
{
	Slot801498EC* base = *(Slot801498EC**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_801498EC(int owner, int* o)
{
	Slot801498EC* s = FindSlot801498EC(owner, 2);
	o[0x54 / 4]     = o[0x54 / 4] + 1;
	if ((unsigned int)s->f4 != 0) {
		fn_801A491C(s->f4);
		s->f4 = 0;
	}
	s->f4 = (int)o;
	return owner;
}
}
