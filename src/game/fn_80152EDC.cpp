// Increments the halfword at +0xE.

extern "C" {
struct Obj80152EDC {
	unsigned char pad[0xe];
	short se;
};

void fn_80152EDC(Obj80152EDC* o)
{
	o->se = o->se + 1;
}
}
