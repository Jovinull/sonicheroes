// Starts the 0x10 state unless it is already active in state 0x3F: sets the flag, counter and raises the speed to the minimum.
struct Pl8004470C {
	unsigned char pad0[0x6F0];
	short f6F0;
	unsigned char pad6F2[2];
	short f6F4;
	volatile short f6F6;
	unsigned char pad6F8[0xC];
	unsigned char pad704[0x80];
	int f784;
	unsigned char pad788[0x38];
	float f7C0;
	float f7C4;
	float f7C8;
	unsigned char pad7CC[0x88];
	float f854;
};

extern "C" {
void fn_8004470C(Pl8004470C* p)
{
	if ((p->f6F6 & 0x1000) == 0 || p->f6F4 != 0x3F) {
		p->f6F6 = p->f6F6 | 0x1000;
		p->f6F4 = 0x10;
		p->f784 = 0xA;
		if (p->f7C0 < p->f854) {
			p->f7C0 = p->f854;
		}
	}
}
}
