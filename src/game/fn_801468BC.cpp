// Replaces the object held at +0x30: releases the old one, stores arg1 and (if non-null) acquires it; returns arg0.

extern "C" {
struct Obj801468BC {
	unsigned char pad[0x30];
	void* f30;
};
void fn_80147288(void*);
void fn_80147918(void*);

Obj801468BC* fn_801468BC(Obj801468BC* o, void* v)
{
	if (o->f30 != 0) {
		fn_80147288(o->f30);
	}
	o->f30 = v;
	if (v != 0) {
		fn_80147918(o->f30);
	}
	return o;
}
}
