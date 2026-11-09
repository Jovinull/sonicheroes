// Replaces the reference stored at slot idx (+8 + idx*4): releases the old one, stores the new one and bumps its count at +0x54; returns the table.

extern "C" {
struct Ref80146920 {
	unsigned char pad[0x54];
	int f54;
};
struct Table80146920 {
	unsigned char pad[8];
	Ref80146920* f8[1];
};
void fn_801A491C(void*);

Table80146920* fn_80146920(Table80146920* t0, int idx, Ref80146920* r)
{
	Table80146920* t = (Table80146920*)((unsigned char*)t0 + idx * 4);
	if (t->f8[0] != 0) {
		fn_801A491C(t->f8[0]);
	}
	t->f8[0] = r;
	if (r != 0) {
		r->f54 = r->f54 + 1;
	}
	return t0;
}
}
