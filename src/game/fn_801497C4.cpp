// Stores -v as float 0x0C (slot of kind 1 of the two 0x18-byte slots in the record the owner points to at
// lbl_8042C858; see fn_80149AB4). Returns the owner.
extern "C" {
struct Slot801497C4 {
	int f0;
	int f4;
	int f8;
	float fc;
	int f10;
	int kind;
};
extern int lbl_8042C858;

static inline Slot801497C4* FindSlot801497C4(int owner, int kind)
{
	Slot801497C4* base = *(Slot801497C4**)(owner + lbl_8042C858);
	unsigned char i;
	for (i = 0; i < 2; i++) {
		if (base[i].kind == kind) {
			return &base[i];
		}
	}
	return 0;
}

int fn_801497C4(int owner, float v)
{
	FindSlot801497C4(owner, 1)->fc = -v;
	return owner;
}
}
