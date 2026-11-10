// Pauses the sound streams: for each entry of lbl_8042B624 in state 1..6 pauses its ADX player (state 2..6) and sets the paused bit (+0x2B bit 0), and does the same for entries of lbl_8042B634 in state 1.
struct Entry800CB84C {
	unsigned char pad0[0x29];
	signed char c29;
	unsigned char pad2A[1];
	unsigned char f2B;
	unsigned char pad2C[0x10];
	int f3C;
	int f40;
	int f44;
};

extern "C" {
extern Entry800CB84C* lbl_8042B624[2];
extern Entry800CB84C* lbl_8042B634[2];
void ADXT_Pause(int h, int on);

void fn_800CB84C(void)
{
	Entry800CB84C* s;
	Entry800CB84C* t;
	unsigned char j;
	unsigned char i;
	for (i = 0; i < 2; i++) {
		s = lbl_8042B624[i];
		if (s != 0) {
			if (s->c29 != 1) {
				if (s->c29 >= 1 && s->c29 < 7) {
					ADXT_Pause(s->f44, 1);
					s->f2B = s->f2B | 1;
				}
			} else {
				s->f2B = s->f2B | 1;
			}
		}
	}
	for (j = 0; j < 2; j++) {
		t = lbl_8042B634[j];
		if (t != 0) {
			switch (t->c29) {
				case 1:
					ADXT_Pause(t->f3C, 1);
					t->f2B = t->f2B | 1;
					break;
			}
		}
	}
}
}
