// Clears the eight per-player slots of the four state tables, resets the selection record to -1, rotates the previous input words and zeroes the pending counters.
struct Quad8002171C {
	int f0;
	int f4;
	int f8;
	int fC;
};
struct SlotC8002171C {
	int f0;
	unsigned char pad[0x1484];
};
struct SlotD8002171C {
	int f0;
	unsigned char pad[0x804];
};

extern "C" {
extern Quad8002171C lbl_802AD060;
extern short lbl_802AD040[8];
extern short lbl_802AD050[8];
extern SlotC8002171C lbl_8029EBC0[8];
extern SlotD8002171C lbl_802A9000[8];
extern short lbl_8042C188;
extern short lbl_8042C18A;
extern unsigned short lbl_8042C18C;
extern unsigned short lbl_8042C18E;
extern unsigned short lbl_8042C190;
extern unsigned short lbl_8042C192;
extern short lbl_8042C194;
extern short lbl_8042C196;
extern short lbl_8042C198;
extern short lbl_8042C19A;
extern short lbl_8042C19C;
extern short lbl_8042C19E;
extern int lbl_8042C1A0;

void fn_8002171C()
{
	int i;
	lbl_802AD060.f0 = 0;
	lbl_802AD060.f4 = -1;
	lbl_802AD060.f8 = -1;
	lbl_802AD060.fC = -1;
	for (i = 0; i < 8; i++) {
		lbl_802AD040[i]    = 0;
		lbl_802AD050[i]    = 0;
		lbl_8029EBC0[i].f0 = 0;
		lbl_802A9000[i].f0 = 0;
	}
	lbl_8042C188 = 0;
	lbl_8042C18A = 0;
	lbl_8042C190 = lbl_8042C18C;
	lbl_8042C192 = lbl_8042C18E;
	lbl_8042C18C = 0;
	lbl_8042C18E = 0;
	lbl_8042C194 = 0;
	lbl_8042C196 = 0;
	lbl_8042C198 = 0;
	lbl_8042C19A = 0;
	lbl_8042C19C = 0;
	lbl_8042C19E = 0;
	lbl_8042C1A0 = 3;
}
}
