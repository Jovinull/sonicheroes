// Stores a and b as words 0x00 and 0x04 (slot of kind 5 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slot80149D7C {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot80149D7C* FindSlot80149D7C(int owner, int kind)
{
	Slot80149D7C* base = *(Slot80149D7C**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149D7C(int owner, int a, int b)
{
	Slot80149D7C* s = FindSlot80149D7C(owner, 5);
	s->f0           = a;
	s->f4           = b;
	return owner;
}
}
