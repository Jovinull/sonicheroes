// Puts the fighter into its hit state: sets flags 4 and 0xC00, timer 0x3C at 0x6AC and starts effect 0x1B for the player in bytes 0x761/0x760.

extern "C" {
struct Fighter80048444 {
	unsigned char pad[0x6ac];
	int f6ac;
	unsigned char pad1[0x6f6 - 0x6b0];
	short flags;
	unsigned char pad2[0x760 - 0x6f8];
	signed char c760;
	signed char c761;
	unsigned char pad3[0x770 - 0x762];
	short f770;
};
void fn_80137D0C(int, int, int);

void fn_80048444(Fighter80048444* o)
{
	o->flags |= 4;
	o->f770 |= 0xc00;
	o->f6ac = 0x3c;
	fn_80137D0C(0x1b, o->c761, o->c760);
}
}
