// Clears the player's timers, runs the common reset and re-arms the speed when a timer is set.
struct Pl800EF9B8 {
	unsigned char pad0[0x63A];
	short f63A;
	short f63C;
	unsigned char pad63E[2];
	int f640;
	unsigned char pad644[0x17C];
	float f7C0;
};

extern "C" {
extern float lbl_8042E3C4;
void fn_800EF28C();

void fn_800EF9B8(Pl800EF9B8* p)
{
	p->f63A = 0;
	p->f63C = 0;
	p->f640 = 0;
	fn_800EF28C();
	if (p->f63C != 0) {
		p->f7C0 = lbl_8042E3C4;
	}
}
}
