// Clears flag bits 0x8 and 0x10 of the object's flags (+4), then clears bit 0x10 in the flags of each of its child objects (pointers from 0x114, count at 0x39).

extern "C" {
struct Child8009250C {
	unsigned char pad[4];
	unsigned short fl;
};
struct Obj8009250C {
	unsigned char pad[4];
	unsigned short fl;
	unsigned char pad1[0x39 - 6];
	signed char c39;
};

void fn_8009250C(Obj8009250C* o)
{
	Obj8009250C** p;
	int i;
	o->fl &= ~8;
	o->fl &= ~0x10;
	i = 0;
	p = (Obj8009250C**)o;
	for (; i < o->c39; i++) {
		Child8009250C* t = (Child8009250C*)p[0x114 / 4];
		if (t != 0 && (((volatile Child8009250C*)t)->fl & 0x10) != 0) {
			t->fl &= ~0x10;
		}
		p++;
	}
}
}
