// Pushes the object's current vector into its 16-entry history ring and advances the write index.
struct V8009AFA4 {
	float x;
	float y;
	float z;
};
struct Obj8009AFA4 {
	unsigned char pad0[0x3E];
	short f3E;
	float f40;
	float f44;
	float f48;
	V8009AFA4 ring[16];
};

extern "C" {
void fn_8009AFA4(Obj8009AFA4* o)
{
	V8009AFA4* e = &o->ring[o->f3E];
	e->x         = o->f40;
	e->y         = o->f44;
	e->z         = o->f48;
	o->f3E++;
	if (o->f3E >= 0x10) {
		o->f3E = 0;
	}
}
}
