// Clears every entry of the eight-word table lbl_802911D4 that equals v (see fn_801B1C9C).
extern "C" {
extern unsigned int lbl_802911D4[8];
void fn_801B1C0C(unsigned int v)
{
	int i;
	for (i = 0; i < 8; i++) {
		if (v == lbl_802911D4[i]) {
			lbl_802911D4[i] = 0;
		}
	}
}
}
