// Stores v as word 0x0C (slot of kind 2 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slot801499DC {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot801499DC* FindSlot801499DC(int owner, int kind)
{
	Slot801499DC* base = *(Slot801499DC**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_801499DC(int owner, int v)
{
	FindSlot801499DC(owner, 2)->fc = v;
	return owner;
}
}
