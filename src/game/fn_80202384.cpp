// Allocates 0x10 bytes with fn_80194318 into the object's word 0xC; returns the object, or 0 on failure.

extern "C" {
struct Obj80202384 {
	unsigned char pad[0xc];
	unsigned fc;
};
unsigned fn_80194318(int);

Obj80202384* fn_80202384(Obj80202384* o)
{
	o->fc = fn_80194318(0x10);
	if (o->fc == 0) {
		return 0;
	}
	return o;
}
}
