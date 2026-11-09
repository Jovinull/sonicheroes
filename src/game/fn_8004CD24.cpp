// Releases the object in slot idx of lbl_802D5B20 (fn_8014D8A4) if any, then stores the new one there.

extern "C" {
extern unsigned lbl_802D5B20[10];
void fn_8014D8A4(unsigned);

void fn_8004CD24(int unused, int idx, unsigned v)
{
	if (lbl_802D5B20[idx] != 0) {
		fn_8014D8A4(lbl_802D5B20[idx]);
		lbl_802D5B20[idx] = 0;
	}
	lbl_802D5B20[idx] = v;
}
}
