// Returns float 0x08 (slot of kind 2 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4).
extern "C" {
struct Slot80149B44 {
	int f0;
	int f4;
	float f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot80149B44* FindSlot80149B44(int owner, int kind)
{
	Slot80149B44* base = *(Slot80149B44**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

float fn_80149B44(int owner)
{
	return FindSlot80149B44(owner, 2)->f8;
}
}
