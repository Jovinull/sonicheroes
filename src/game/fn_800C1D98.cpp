// Removes the id lbl_8042B408[idx] from the 64-entry table lbl_803042C8 and marks control record idx (lbl_80304408) as inactive.
struct Ctl800C1D98 {
	unsigned char pad0[0x4c];
	int f4C;
};

extern "C" {
extern unsigned int lbl_803042C8[];
extern Ctl800C1D98* lbl_80304408[];
extern unsigned int lbl_8042B408[2];

void fn_800C1D98(int idx)
{
	Ctl800C1D98* c = lbl_80304408[idx];
	int i;
	if (c != 0 && c->f4C == 1) {
		c->f4C = i = 0;
		{
			unsigned int id = lbl_8042B408[idx];
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
