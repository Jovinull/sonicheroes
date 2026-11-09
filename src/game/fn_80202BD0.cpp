// Allocates 0x90 bytes with fn_80194318 into the object's word 0x10; returns the object, or 0 on failure.

extern "C" {
struct Obj80202BD0 {
	unsigned char pad[0x10];
	unsigned f10;
};
unsigned fn_80194318(int);

Obj80202BD0* fn_80202BD0(Obj80202BD0* o)
{
	o->f10 = fn_80194318(0x90);
	if (o->f10 == 0) {
		return 0;
	}
	return o;
}
}
