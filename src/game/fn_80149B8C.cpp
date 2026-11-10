// Finds the slot of kind 4, bumps the object's reference count, releases the slot's previous object, stores the new one and fires events 2 and 1; returns the owner.
extern "C" {
struct Slot80149B8C {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;
void fn_801A491C(int p);
void fn_80142E38(Slot80149B8C* s, int c);

static inline Slot80149B8C* FindSlot80149B8C(int owner, int kind)
{
	Slot80149B8C* base = *(Slot80149B8C**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149B8C(int owner, int* o)
{
	Slot80149B8C* s = FindSlot80149B8C(owner, 4);
	o[0x54 / 4]     = o[0x54 / 4] + 1;
	if ((unsigned int)s->f0 != 0) {
		fn_801A491C(s->f0);
		s->f0 = 0;
	}
	s->f0 = (int)o;
	fn_80142E38(s, 2);
	fn_80142E38(s, 1);
	return owner;
}
}
