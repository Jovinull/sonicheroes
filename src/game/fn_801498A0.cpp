// Returns minus float 0x0C (slot of kind 1 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4).
extern "C" {
struct Slot801498A0 {
	int f0;
	int f4;
	int f8;
	float fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot801498A0* FindSlot801498A0(int owner, int kind)
{
	Slot801498A0* base = *(Slot801498A0**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

float fn_801498A0(int owner)
{
	return -FindSlot801498A0(owner, 1)->fc;
}
}
