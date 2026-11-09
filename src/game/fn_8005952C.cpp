// Marks the global as initialised and sets bit 4 in each of the 0x800 table entries (64-byte stride), remembering the last one in lbl_8042C290; the running index lives at +0x830.

extern "C" {
struct Obj8005952C {
	unsigned char pad[0x830];
	int f830;
};
struct Entry8005952C {
	unsigned char pad[0x18];
	unsigned f18;
	unsigned char pad1[0x40 - 0x1c];
};
extern int lbl_8042C28C;
extern void* lbl_8042C290;
extern Entry8005952C lbl_802D63A0[];

void fn_8005952C(Obj8005952C* o)
{
	lbl_8042C28C = 1;
	o->f830      = 0;
	while (o->f830 < 0x800) {
		Entry8005952C* e = &lbl_802D63A0[o->f830];
		lbl_8042C290     = e;
		e->f18 |= 4;
		o->f830 = o->f830 + 1;
	}
}
}
