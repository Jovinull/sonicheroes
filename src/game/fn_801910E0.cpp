// When the state at +0xE7 is below 8, sets flag 4 at +0x30 and stores 8 at +0xE8.

extern "C" {
struct Obj801910E0 {
	unsigned char pad[0x30];
	unsigned f30;
	unsigned char pad1[0xe7 - 0x34];
	unsigned char ce7;
	unsigned char ce8;
};

void fn_801910E0(Obj801910E0* o)
{
	if (o->ce7 < 8) {
		o->f30 |= 4;
		o->ce8 = 8;
	}
}
}
