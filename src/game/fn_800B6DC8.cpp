// When the flag lbl_8042C3C8 is set, clears bit 8 in the entries returned by fn_801439D8 for the three handles lbl_8042C390/94/98 (where set), then clears the flag.

extern "C" {
extern int lbl_8042C3C8;
extern unsigned lbl_8042C390;
extern unsigned lbl_8042C394;
extern unsigned lbl_8042C398;
unsigned* fn_801439D8(unsigned);

void fn_800B6DC8(void)
{
	unsigned* t;
	if (lbl_8042C3C8 != 0) {
		if (lbl_8042C390 != 0) {
			t = fn_801439D8(lbl_8042C390);
			if (t != 0) {
				*t &= ~8;
			}
		}
		if (lbl_8042C394 != 0) {
			t = fn_801439D8(lbl_8042C394);
			if (t != 0) {
				*t &= ~8;
			}
		}
		if (lbl_8042C398 != 0) {
			t = fn_801439D8(lbl_8042C398);
			if (t != 0) {
				*t &= ~8;
			}
		}
		lbl_8042C3C8 = 0;
	}
}
}
