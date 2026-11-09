// Marks the object in slot idx of lbl_802AD090 (flag 0x1000, halfword 4 = v) and stores w in field 0x24 of the matching lbl_802AD0D0 entry.

extern "C" {
struct Rec800E1208 {
	unsigned char pad[4];
	short s4;
	short s6;
};
struct Other800E1208 {
	unsigned char pad[0x24];
	int f24;
};
extern Rec800E1208* lbl_802AD090[];
extern Other800E1208* lbl_802AD0D0[];

void fn_800E1208(int idx, signed char v, int w)
{
	Rec800E1208* r = lbl_802AD090[idx];
	if (r != 0) {
		r->s6 |= 0x1000;
		r->s4                  = v;
		lbl_802AD0D0[idx]->f24 = w;
	}
}
}
