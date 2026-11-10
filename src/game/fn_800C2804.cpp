// Removes the id lbl_8042B3F8[idx] from the 64-entry table lbl_803042C8 and marks control record idx (lbl_803043E8) as inactive.
struct Ctl800C2804 {
	unsigned char pad0[0x3c];
	int f3C;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern Ctl800C2804* lbl_803043E8[];
extern unsigned int lbl_8042B3F8[2];

void fn_800C2804(int idx)
{
	Ctl800C2804* c = lbl_803043E8[idx];
	int i;
	if (c != 0 && c->f3C == 1) {
		c->f3C = i = 0;
		{
			unsigned int id = lbl_8042B3F8[idx];
			for (; i < 0x40; i++) {
				unsigned int v = lbl_803042C8[i];
				if (v == id) {
					lbl_803042C8[i] = 0;
					return;
				}
			}
		}
	}
}
}
