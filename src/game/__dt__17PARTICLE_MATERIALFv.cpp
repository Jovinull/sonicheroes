// Destructor (PARTICLE_MATERIAL): installs the vtable lbl_80243BF8 at +0x54, runs fn_80064CA8 and frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void fn_80064CA8(void*);
struct Material17PARTICLE_MATERIAL {
	unsigned char pad[0x54];
	void* f54;
};
extern unsigned char lbl_80243BF8[];

Material17PARTICLE_MATERIAL* __dt__17PARTICLE_MATERIALFv(
    Material17PARTICLE_MATERIAL* o, short flags)
{
	if (o != 0) {
		o->f54 = lbl_80243BF8;
		fn_80064CA8(o);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
