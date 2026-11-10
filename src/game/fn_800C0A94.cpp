// Registers the id lbl_8042C420 in the first free slot of the 64-entry table lbl_803042C8 and marks the control record as active.
struct Ctl800C0A94 {
	unsigned char pad0[0x44];
	int f44;
	int f48;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern unsigned int lbl_8042C420;
extern Ctl800C0A94* lbl_8042C424;

void fn_800C0A94()
{
	Ctl800C0A94* c = lbl_8042C424;
	int i;
	if (c != 0 && c->f44 == 0) {
		c->f44 = 1;
		c->f48 = i = 0;
		{
			unsigned int id = lbl_8042C420;
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
