// Stores v as float 0x8 of the slot of kind 2 (of the two 0x18-byte slots in the record the
// owner points to at lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slotfn_80149A24 {
	int f0;
	int f4;
	float f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slotfn_80149A24* FindSlotfn_80149A24(int owner, int kind)
{
	Slotfn_80149A24* base = *(Slotfn_80149A24**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_80149A24(int owner, float v)
{
	FindSlotfn_80149A24(owner, 2)->f8 = v;
	return owner;
}
}
