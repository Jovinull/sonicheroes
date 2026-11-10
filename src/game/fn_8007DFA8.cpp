// Enters the 0x3D action: sets its counters and speed and swaps the flag bits.
struct Pl8007DFA8 {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[4];
	short f6F6;
	unsigned char pad6F8[0xC8];
	float f7C0;
	unsigned char pad7C4[0xEA];
	short f8AE;
	unsigned char pad8B0[0x198];
	short fA48;
	short fA4A;
	unsigned char padA4C[2];
	short fA4E;
};

extern "C" {
extern float lbl_8042D788;

void fn_8007DFA8(Pl8007DFA8* p)
{
	p->f6F0 = 0x3D;
	p->f8AE = 0x5A;
	p->fA48 = 0xA;
	p->fA4A = 0;
	p->fA4E = 0;
	p->f7C0 = lbl_8042D788;
	p->f6F6 = p->f6F6 & 0xFFFFFEFF;
	p->f6F6 = p->f6F6 | 0x400;
}
}
