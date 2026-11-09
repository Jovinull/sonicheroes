// ORs the flags into the halfword at 0xC; when flag 1 is among them and a handle is held at 0x54, releases it (fn_801559E4) and clears it; returns the object.

extern "C" {
struct Obj80152828 {
	unsigned char pad[0xc];
	unsigned short fc;
	unsigned char pad1[0x54 - 0xe];
	unsigned f54;
};
void fn_801559E4(unsigned);

Obj80152828* fn_80152828(Obj80152828* o, int v)
{
	o->fc |= v;
	if ((v & 1) && o->f54 != 0) {
		fn_801559E4(o->f54);
		o->f54 = 0;
	}
	return o;
}
}
