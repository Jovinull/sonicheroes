// Allocates the 0x3C-byte buffer stored at +8; returns the object, or 0 if the allocation fails.

extern "C" {
struct Obj80203DF0 {
	unsigned char pad[8];
	unsigned f8;
};
unsigned fn_80194318(int);

Obj80203DF0* fn_80203DF0(Obj80203DF0* o)
{
	unsigned t = fn_80194318(0x3c);
	o->f8      = t;
	if (t == 0) {
		return 0;
	}
	return o;
}
}
