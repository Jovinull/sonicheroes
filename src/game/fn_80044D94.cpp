// Enters the 0xC action: unless the mode is 2 or 3, picks sub-state 0x1E or 0x1D depending on the measured value against lbl_8042D1BC.
struct Mode80044D94 {
	unsigned char pad0[0x140];
	int f140;
};
struct Sub80044D94 {
	unsigned char pad0[0x14E];
	short f14E;
	unsigned char pad150[0x108];
	Mode80044D94* f258;
};
struct Pl80044D94 {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[0x6E];
	Sub80044D94 sub;
};

extern "C" {
extern float lbl_8042D1BC;
float fn_800DAD94(void* a, void* b, void* c);

void fn_80044D94(Pl80044D94* p)
{
	short* st      = &p->f6F0;
	char* q        = (char*)p + 0x720;
	Sub80044D94* s = &p->sub;
	int m;
	*st = 0xC;
	m   = s->f258->f140;
	if (m != 2 && m != 3) {
		if (fn_800DAD94(st, q, s) < lbl_8042D1BC) {
			s->f14E = 0x1E;
			return;
		}
		s->f14E = 0x1D;
	}
}
}
