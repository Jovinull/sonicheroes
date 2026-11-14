// Stores v as word 0x00 (slot of kind 1 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slot8014977C {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot8014977C* FindSlot8014977C(int owner, int kind)
{
	Slot8014977C* base = *(Slot8014977C**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_8014977C(int owner, int v)
{
	FindSlot8014977C(owner, 1)->f0 = v;
	return owner;
}
}
