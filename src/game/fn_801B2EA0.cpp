// Stores a in the slot (or, for 0, restores the slot's saved value at 0x1C, else clears it) of the table at lbl_8042C9A4 + lbl_8042CA74; returns the slot.

extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042CA74;
struct Slot801B2EA0 {
	unsigned f0;
	unsigned char pad[0x18];
	unsigned f1c;
};

unsigned fn_801B2EA0(unsigned a)
{
	if (a != 0) {
		*(unsigned*)(lbl_8042C9A4 + lbl_8042CA74) = a;
	} else {
		Slot801B2EA0* r = (Slot801B2EA0*)(lbl_8042C9A4 + lbl_8042CA74);
		unsigned t      = r->f1c;
		if (t != 0) {
			r->f0 = t;
		} else {
			r->f0 = 0;
		}
	}
	return *(unsigned*)(lbl_8042C9A4 + lbl_8042CA74);
}
}
