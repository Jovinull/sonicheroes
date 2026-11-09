// Resets the player slot k: sets the two animation states (+0x14C / +0x1BC) to 0x10, runs fn_800F2224 on the ones that have a handle, then clears the four per-slot table entries.

extern "C" {
struct Slot8003EDA8 {
	unsigned char pad[0x14c];
	short s14c;
	unsigned char pad1[0x18c - 0x14e];
	unsigned f18c;
	unsigned char pad2[0x1bc - 0x190];
	short s1bc;
	unsigned char pad3[0x1fc - 0x1be];
	unsigned f1fc;
};
extern Slot8003EDA8* lbl_802AD0D0[];
extern int lbl_802AD070[];
extern int lbl_802AD090[];
extern int lbl_802AD0B0[];
void fn_800F2224(void*, int);

void fn_8003EDA8(int k)
{
	Slot8003EDA8* c = lbl_802AD0D0[k];
	c->s14c         = 0x10;
	if (c->f18c != 0) {
		fn_800F2224((unsigned char*)c + 0x14c, 1);
	}
	c->s1bc = 0x10;
	if (c->f1fc != 0) {
		fn_800F2224((unsigned char*)c + 0x1bc, 1);
	}
	lbl_802AD070[k] = 0;
	lbl_802AD090[k] = 0;
	lbl_802AD0B0[k] = 0;
	lbl_802AD0D0[k] = 0;
}
}
