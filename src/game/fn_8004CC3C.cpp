// Takes the pending team index (lbl_8042C22C) as the current one, points the
// current-team record pointer at its 0x2324-byte record (plus 0x40), and clears
// the pending index. Returns 0 when nothing is pending.

extern "C" {
extern unsigned char lbl_802B908C[];
extern int lbl_8042C1FC;
extern int lbl_8042C22C;
extern unsigned char* lbl_8042C208;

int fn_8004CC3C()
{
	int t = lbl_8042C22C;
	if (t >= 0) {
		lbl_8042C1FC = t;
		lbl_8042C208 = lbl_802B908C + t * 0x2324 + 0x40;
		lbl_8042C22C = -1;
		return 1;
	}
	return 0;
}
}
