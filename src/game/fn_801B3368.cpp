// Releases every used slot (+0x14, 0x1C bytes each, count at +2) of the table: frees pending buffers via fn_801B6EAC unless flagged, clears the slot, then clears the table's state at +0.

extern "C" {
struct Hdr801B3368 {
	unsigned char pad[0x10];
	int f10;
};
struct Slot801B3368 {
	int f0;
	unsigned f4;
	int f8;
	int fc;
	int f10;
	unsigned f14;
	int f18;
};
struct Table801B3368 {
	unsigned short s0;
	unsigned short s2;
	Hdr801B3368* f4;
};
extern int lbl_8042CA8C;
void fn_801B6EAC(int, unsigned);

void fn_801B3368(Table801B3368* o)
{
	int n;
	Slot801B3368* p;
	p          = (Slot801B3368*)((unsigned char*)o + 0x14);
	o->f4->f10 = 1;
	n          = o->s2;
	do {
		if (p->f14 != 0) {
			if (p->f4 != 0 && !(*(unsigned short*)p & 2)) {
				fn_801B6EAC(lbl_8042CA8C, p->f4);
			}
			p->f0  = 0;
			p->f4  = 0;
			p->fc  = 0;
			p->f10 = 0;
			p->f14 = 0;
		}
		n--;
		p = (Slot801B3368*)((unsigned char*)p + 0x1c);
	} while (n != 0);
	o->s0 = 0;
}
}
