// Returns the float that the pointer at offset 0x18 of an object points to.
struct Obj802012B8 {
	unsigned char pad0[0x18];
	float* f18;
};

extern "C" {
float fn_802012B8(Obj802012B8* o)
{
	return *o->f18;
}
}
