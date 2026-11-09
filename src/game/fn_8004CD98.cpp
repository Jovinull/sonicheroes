// Selects team `i` (both lbl_8042C21C and lbl_8042C224) when it is below lbl_8042C204; returns whether it did.

extern "C" {
extern int lbl_8042C204;
extern int lbl_8042C21C;
extern int lbl_8042C224;

int fn_8004CD98(int unused, int i)
{
	if (i >= lbl_8042C204) {
		return 0;
	}
	lbl_8042C21C = i;
	lbl_8042C224 = i;
	return 1;
}
}
