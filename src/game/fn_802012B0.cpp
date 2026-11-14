// Returns the float at offset 0x08 of an object.
struct Obj802012B0 {
	unsigned char pad0[0x8];
	float f8;
};

extern "C" {
float fn_802012B0(Obj802012B0* o)
{
	return o->f8;
}
}
