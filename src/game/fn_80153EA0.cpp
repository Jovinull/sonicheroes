// Stores the float at +0x14 and, when the owned handle at +4 is set, calls fn_8019E880 on it; returns the object.
struct Obj80153EA0 {
	unsigned char pad0[4];
	unsigned int f4;
	unsigned char pad8[0xC];
	float f14;
};

extern "C" {
void fn_8019E880(unsigned int a);

Obj80153EA0* fn_80153EA0(Obj80153EA0* o, float v)
{
	unsigned int t = o->f4;
	o->f14         = v;
	if (t != 0) {
		fn_8019E880(t);
	}
	return o;
}
}
