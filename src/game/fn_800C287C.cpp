// Registers the id lbl_8042B3F8[idx] in the first free slot of the 64-entry table lbl_803042C8 and marks control record idx (lbl_803043E8) as active.
struct Ctl800C287C {
	unsigned char pad0[0x3c];
	int f3C;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern Ctl800C287C* lbl_803043E8[];
extern unsigned int lbl_8042B3F8[2];

void fn_800C287C(int idx)
{
	Ctl800C287C* c = lbl_803043E8[idx];
	int i;
	if (c != 0 && c->f3C == 0) {
		c->f3C = 1;
		{
			unsigned int id = lbl_8042B3F8[idx];
			for (i = 0; i < 0x40; i++) {
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
