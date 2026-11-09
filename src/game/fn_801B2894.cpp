// Returns whether the draw sync token has passed the given value, reading the hardware counter first.
extern "C" {
extern volatile unsigned short lbl_8042BE88;
extern volatile unsigned short lbl_8042CA68;
unsigned short GXReadDrawSync();

int fn_801B2894(unsigned short a)
{
	int r;
	lbl_8042CA68 = GXReadDrawSync();
	if (lbl_8042CA68 >= 0xE000) {
		return 0;
	}
	if (lbl_8042BE88 >= lbl_8042CA68) {
		r = 0;
		if (a <= lbl_8042CA68 || a > lbl_8042BE88) {
			r = 1;
		}
		return r;
	}
	r = 0;
	if (a > lbl_8042BE88 && a <= lbl_8042CA68) {
		r = 1;
	}
	return r;
}
}
