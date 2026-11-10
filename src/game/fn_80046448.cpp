// Ends the action when the value reaches its limit: picks the follow-up mode by the threshold, clears the flag bits and returns whether it ended.
struct St80046448 {
	short f0;
	unsigned char pad2[4];
	short f6;
};
struct Sub80046448 {
	unsigned char pad0[0x18];
	short f18;
	unsigned char pad1A[0x46];
	float f60;
	unsigned char pad64[0x88];
	float fEC;
	unsigned char padF0[0x5E];
	short f14E;
};

extern "C" {
extern float lbl_8042D1BC;

int fn_80046448(St80046448* st, int unused, Sub80046448* s)
{
	float t = s->f60;
	if (t < s->fEC) {
		if (t <= lbl_8042D1BC) {
			st->f0 = 0;
			s->f18 = 0;
		} else {
			st->f0 = 0xE;
		}
		s->f14E = 0x1A;
		st->f6  = st->f6 & ~0x500;
		return 1;
	}
	return 0;
}
}
