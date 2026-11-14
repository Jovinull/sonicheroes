// Returns the float behind the pointer at offset 0x14 of an object, or behind the one at 0x18
// when the first is null.
struct Obj80201370 {
	unsigned char pad0[0x14];
	float* f14;
	float* f18;
};

extern "C" {
float fn_80201370(Obj80201370* o)
{
	if (o->f14 != 0) {
		return *o->f14;
	}
	return *o->f18;
}
}
