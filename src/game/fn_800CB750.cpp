// Resumes the sound streams: for each entry of lbl_8042B624 in state 2..6 un-pauses its ADX player, and for each entry of lbl_8042B634 in state 1 un-pauses its player, clearing the paused bit (+0x2B bit 0).
struct Entry800CB750 {
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
extern Entry800CB750* lbl_8042B624[2];
extern Entry800CB750* lbl_8042B634[2];
void ADXT_Pause(int h, int on);

void fn_800CB750(void)
{
	Entry800CB750* t;
	unsigned char j;
	unsigned char i;
	Entry800CB750* s;
	for (i = 0; i < 2; i++) {
		s = lbl_8042B624[i];
		if (s != 0) {
			switch (s->c29) {
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					ADXT_Pause(s->f44, 0);
					break;
			}
			s->f2B = s->f2B & 0xFFFFFFFE;
		}
	}
	for (j = 0; j < 2; j++) {
		t = lbl_8042B634[j];
		if (t != 0) {
			switch (t->c29) {
				case 1:
					ADXT_Pause(t->f3C, 0);
					t->f2B = t->f2B & 0xFFFFFFFE;
					break;
			}
		}
	}
}
}
