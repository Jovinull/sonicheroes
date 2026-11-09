// Allocates the two buffers stored at +0x18 (4 bytes) and +0x14 (0x10 bytes); returns the object, or 0 if an allocation fails.

extern "C" {
struct Obj80202E8C {
	unsigned char pad[0x14];
	unsigned f14;
	unsigned f18;
};
unsigned fn_80194318(int);

Obj80202E8C* fn_80202E8C(Obj80202E8C* o)
{
	unsigned t = fn_80194318(4);
	o->f18     = t;
	if (t == 0) {
		return 0;
	}
	t      = fn_80194318(0x10);
	o->f14 = t;
	if (t == 0) {
		return 0;
	}
	return o;
}
}
