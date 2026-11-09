// For the player with byte 0x761 == 4: releases the four handles at 0xB2C, 0xB30, 0xB34 and 0xB38 with fn_8005FD8C(handle, -1) and clears them.

extern "C" {
struct Obj80067050 {
	unsigned char pad[0x761];
	signed char c761;
	unsigned char pad1[0xb2c - 0x762];
	unsigned fb2c;
	unsigned fb30;
	unsigned fb34;
	unsigned fb38;
};
void fn_8005FD8C(unsigned, int);

void fn_80067050(Obj80067050* o)
{
	if (o->c761 == 4) {
		if (o->fb2c != 0) {
			fn_8005FD8C(o->fb2c, -1);
			o->fb2c = 0;
		}
		if (o->fb30 != 0) {
			fn_8005FD8C(o->fb30, -1);
			o->fb30 = 0;
		}
		if (o->fb34 != 0) {
			fn_8005FD8C(o->fb34, -1);
			o->fb34 = 0;
		}
		if (o->fb38 != 0) {
			fn_8005FD8C(o->fb38, -1);
			o->fb38 = 0;
		}
	}
}
}
