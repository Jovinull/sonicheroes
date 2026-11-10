// Finds the slot of kind 4, stores two values into it and fires events 0xA and 0xB; returns the owner.
extern "C" {
struct Slot80149C4C {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;
void fn_80142E38(Slot80149C4C* s, int c);

static inline Slot80149C4C* FindSlot80149C4C(int owner, int kind)
{
	Slot80149C4C* base = *(Slot80149C4C**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149C4C(int owner, int b, int c)
{
	Slot80149C4C* s = FindSlot80149C4C(owner, 4);
	s->f4           = b;
	s->f8           = c;
	fn_80142E38(s, 0xA);
	fn_80142E38(s, 0xB);
	return owner;
}
}
