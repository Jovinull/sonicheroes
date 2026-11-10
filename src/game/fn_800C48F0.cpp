// Clears the first table entry equal to the given id.
extern "C" {
extern unsigned int lbl_803042C8[];

void fn_800C48F0(int unused, unsigned int id)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		unsigned int v = lbl_803042C8[i];
		if (v == id) {
			lbl_803042C8[i] = 0;
			return;
		}
	}
}
}
