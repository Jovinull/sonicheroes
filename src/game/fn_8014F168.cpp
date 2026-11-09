// Runs fn_8014F854 on the object when flag 2 of the word at 0x4C is set, sets bit 0 of byte 3 and returns the object.

extern "C" {
struct Obj8014F168 {
	unsigned char b0, b1, b2, b3;
	unsigned char pad[0x48];
	unsigned f4c;
};
void fn_8014F854(void*);

Obj8014F168* fn_8014F168(Obj8014F168* o)
{
	if (o->f4c & 2) {
		fn_8014F854(o);
	}
	o->b3 |= 1;
	return o;
}
}
