// Marks the effect object `i` (flag 4) and its slot (flags 0x1000, state 9) and sets its word 0x24 to 0x54 or 0x2E depending on flag 0x8000 of the object.

extern "C" {
struct Obj800E1194 {
	unsigned char pad[0x20];
	int f20;
	unsigned char pad1[0x158 - 0x24];
	short f158;
	unsigned char pad2[0x24c - 0x15a];
};
struct Slot800E1194 {
	unsigned char pad[4];
	short s4;
	short s6;
};
struct Out800E1194 {
	unsigned char pad[0x24];
	int f24;
};
extern Slot800E1194* lbl_802AD090[];
extern Obj800E1194* lbl_802AD0D0[];

void fn_800E1194(int i)
{
	Obj800E1194* r = lbl_802AD0D0[i];
	int v;
	Slot800E1194* q;
	if ((r->f20 & 0x8000) != 0) {
		v = 0x54;
	} else {
		v = 0x2e;
	}
	r->f158 |= 4;
	q = lbl_802AD090[i];
	if (q != 0) {
		q->s6 |= 0x1000;
		q->s4                                = 9;
		((Out800E1194*)lbl_802AD0D0[i])->f24 = v;
	}
}
}
