// Runs fn_8019DFDC with the object and either its parent's record at +0xA0 (when there is a parent at +4) or itself; returns arg0.

extern "C" {
struct Obj8019E2E8 {
	unsigned char pad[4];
	Obj8019E2E8* f4;
	unsigned char pad1[0x98];
	Obj8019E2E8* fa0;
};
void fn_8019DFDC(Obj8019E2E8*, Obj8019E2E8*);

Obj8019E2E8* fn_8019E2E8(Obj8019E2E8* o)
{
	Obj8019E2E8* t = o->f4;
	if (t != 0) {
		fn_8019DFDC(o, t->fa0);
	} else {
		fn_8019DFDC(o, o);
	}
	return o;
}
}
