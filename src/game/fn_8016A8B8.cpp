// Replaces the reference at +0x68: sets/clears flag 2 at +0x64 depending on whether arg1 is non-null (bumping its count at +0x54), releases the old one; returns arg0.

extern "C" {
struct Obj8016A8B8 {
	unsigned char pad[0x54];
	int f54;
	unsigned char pad1[0x64 - 0x58];
	unsigned f64;
	void* f68;
};
void fn_801A491C(void*);

Obj8016A8B8* fn_8016A8B8(Obj8016A8B8* o, Obj8016A8B8* r)
{
	if (r != 0) {
		o->f64 |= 2;
		r->f54 = r->f54 + 1;
	} else {
		o->f64 &= ~2;
	}
	if (o->f68 != 0) {
		fn_801A491C(o->f68);
	}
	o->f68 = r;
	return o;
}
}
