// Returns word 0 of the slot of kind 4 (of the two 0x18-byte slots in the record the owner points to at lbl_8042C858).

extern "C" {
struct Slot80149CE0 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot80149CE0* FindSlot80149CE0(int owner, int kind)
{
	Slot80149CE0* base = *(Slot80149CE0**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149CE0(int owner)
{
	return FindSlot80149CE0(owner, 4)->f0;
}
}
