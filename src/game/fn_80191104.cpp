// Sets flag 2 in the word at 0x30 and returns 7 when byte 0xE3 is non-zero; otherwise returns 1.

extern "C" {
struct Obj80191104 {
	unsigned char pad[0x30];
	unsigned f30;
	unsigned char pad1[0xe3 - 0x34];
	unsigned char be3;
};

int fn_80191104(Obj80191104* o)
{
	if (o->be3 != 0) {
		o->f30 |= 2;
		return 7;
	}
	return 1;
}
}
