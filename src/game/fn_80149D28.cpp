// Copies words 0x04 and 0x08 to *a and *b (slot of kind 4 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slot80149D28 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot80149D28* FindSlot80149D28(int owner, int kind)
{
	Slot80149D28* base = *(Slot80149D28**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149D28(int owner, int* a, int* b)
{
	Slot80149D28* s = FindSlot80149D28(owner, 4);
	*a              = s->f4;
	*b              = s->f8;
	return owner;
}
}
