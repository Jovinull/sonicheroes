// For each of the two entries in lbl_8042B624, sets the state at +0x29 to 4 when it is 2, 3, 5 or 6.

extern "C" {
struct Entry800CB6EC {
	unsigned char pad[0x29];
	signed char c29;
};
extern Entry800CB6EC* lbl_8042B624[2];

void fn_800CB6EC(void)
{
	Entry800CB6EC* s;
	signed char c;
	unsigned char i;
	for (i = 0; i < 2; i++) {
		s = lbl_8042B624[i];
		if (s != 0) {
			c = s->c29;
			if (c != 4) {
				if (c < 4) {
					if (c >= 2) {
						goto st;
					}
				} else if (c < 7) {
				st:
					s->c29 = 4;
				}
			}
		}
	}
}
}
