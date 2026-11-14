// Copies words 0x00 and 0x04 to *a and *b, skipping null outputs (slot of kind 5 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slot80149DC8 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot80149DC8* FindSlot80149DC8(int owner, int kind)
{
	Slot80149DC8* base = *(Slot80149DC8**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149DC8(int owner, int* a, int* b)
{
	Slot80149DC8* s = FindSlot80149DC8(owner, 5);
	if (a != 0) {
		*a = s->f0;
	}
	if (b != 0) {
		*b = s->f4;
	}
	return owner;
}
}
