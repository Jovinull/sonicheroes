// Switches to the team record at the given index (records are 0x2324 bytes),
// saving the previous index as pending. Returns 0 if one is already pending.

extern "C" {
extern unsigned char lbl_802B908C[];
extern int lbl_8042C1FC;
extern int lbl_8042C22C;
extern unsigned char* lbl_8042C208;

int fn_8004CC7C(int unused, int index)
{
	if (lbl_8042C22C < 0) {
		lbl_8042C22C = lbl_8042C1FC;
		lbl_8042C1FC = index;
		lbl_8042C208 = lbl_802B908C + index * 0x2324 + 0x40;
		return 1;
	}
	return 0;
}
}
