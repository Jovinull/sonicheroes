// Registers the id lbl_8042C418 in the first free slot of the 64-entry table lbl_803042C8 and marks the control record as active.
struct Ctl800C0E34 {
	unsigned char pad0[0x44];
	int f44;
	int f48;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern unsigned int lbl_8042C418;
extern Ctl800C0E34* lbl_8042C41C;

void fn_800C0E34()
{
	Ctl800C0E34* c = lbl_8042C41C;
	int i;
	if (c != 0 && c->f44 == 0) {
		c->f44 = 1;
		c->f48 = i = 0;
		{
			unsigned int id = lbl_8042C418;
			for (; i < 0x40; i++) {
				unsigned int v = lbl_803042C8[i];
				if (v == 0) {
					lbl_803042C8[i] = id;
					return;
				}
			}
		}
	}
}
}
