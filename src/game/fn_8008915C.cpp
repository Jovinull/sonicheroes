// Reports whether the word at +0x628 of the object is zero.
struct Obj8008915C {
	unsigned char pad0[0x628];
	int f628; // 0x628
};

extern "C" {
int fn_8008915C(Obj8008915C* o)
{
	return !o->f628 ? 1 : 0;
}
}
