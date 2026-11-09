// Replaces the reference stored at *arg0 with arg1: bumps arg1's count (+0x54), releases the old reference; returns arg0.

extern "C" {
struct Ref8015498C {
	unsigned char pad[0x54];
	int f54;
};
void fn_801A491C(void*);

Ref8015498C** fn_8015498C(Ref8015498C** o, Ref8015498C* r)
{
	if (r != 0) {
		r->f54 = r->f54 + 1;
	}
	if (*o != 0) {
		fn_801A491C(*o);
	}
	*o = r;
	return o;
}
}
