// Stores the id in the first free slot of the 64-entry table lbl_803042C8.
extern "C" {
extern unsigned int lbl_803042C8[];

void fn_800C4938(int unused, unsigned int id)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		unsigned int v = lbl_803042C8[i];
		if (v == 0) {
			lbl_803042C8[i] = id;
			return;
		}
	}
}
}
