// Releases the buffer at word 0x10 with fn_80194628 and clears it, if set; returns the object.

extern "C" {
struct Obj80202C1C {
	unsigned char pad[0x10];
	unsigned f10;
};
void fn_80194628(unsigned);

Obj80202C1C* fn_80202C1C(Obj80202C1C* o)
{
	if (o->f10 != 0) {
		fn_80194628(o->f10);
		o->f10 = 0;
	}
	return o;
}
}
