// When either of the two handles (0x678 / 0x680) is set and the state is not already (flag 0x1000, mode 0x3F), raises flag 0x1000 and switches to mode 0x2E.

extern "C" {
struct Obj8004443C {
	unsigned char pad[0x678];
	unsigned f678;
	unsigned char pad1[4];
	unsigned f680;
	unsigned char pad2[0x6f4 - 0x684];
	short s6f4;
	short s6f6;
};

void fn_8004443C(Obj8004443C* o)
{
	if (((o->s6f6 & 0x1000) == 0 || o->s6f4 != 0x3f) && (o->f678 != 0 || o->f680 != 0)) {
		o->s6f6 |= 0x1000;
		o->s6f4 = 0x2e;
	}
}
}
