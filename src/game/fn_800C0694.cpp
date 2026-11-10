// Registers the id lbl_8042C410 in the last free slot of the 64-entry table lbl_803042C8 (searching backwards), marks the record active and sets its timer to 0xF0.
struct Ctl800C0694 {
	unsigned char pad0[0x44];
	int f44;
	int f48;
	int f4C;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern unsigned int lbl_8042C410;
extern Ctl800C0694* lbl_8042C414;

void fn_800C0694()
{
	Ctl800C0694* c = lbl_8042C414;
	int i;
	if (c != 0 && c->f44 == 0) {
		c->f44 = 1;
		c->f48 = 0;
		c->f4C = 0xF0;
		{
			unsigned int id = lbl_8042C410;
			for (i = 0x3F; i >= 0; i--) {
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
