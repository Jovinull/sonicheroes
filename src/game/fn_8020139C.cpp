// Sets or clears flag 2 of the word at 0xC depending on the argument.

extern "C" {
struct Obj8020139C {
	unsigned char pad[0xc];
	unsigned fc;
};

void fn_8020139C(Obj8020139C* o, int v)
{
	if (v != 0) {
		o->fc |= 2;
		return;
	}
	o->fc &= ~2u;
}
}
