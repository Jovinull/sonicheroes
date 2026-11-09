// For the player with byte 0x761 == 3: releases the two handles at 0xA88 and 0xA8C with fn_8005FD8C(handle, -1) and clears them.

extern "C" {
struct Obj8007D064 {
	unsigned char pad[0x761];
	signed char c761;
	unsigned char pad1[0xa88 - 0x762];
	unsigned fa88;
	unsigned fa8c;
};
void fn_8005FD8C(unsigned, int);

void fn_8007D064(Obj8007D064* o)
{
	if (o->c761 == 3) {
		if (o->fa88 != 0) {
			fn_8005FD8C(o->fa88, -1);
			o->fa88 = 0;
		}
		if (o->fa8c != 0) {
			fn_8005FD8C(o->fa8c, -1);
			o->fa8c = 0;
		}
	}
}
}
