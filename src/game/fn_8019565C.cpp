// Clears bits 0 and 1 and bit 17 of the flags at +0xC.

extern "C" {
struct Obj8019565C {
	unsigned char pad[0xc];
	unsigned fc;
};

void fn_8019565C(Obj8019565C* o)
{
	o->fc = o->fc & 0xfffdfffc;
}
}
