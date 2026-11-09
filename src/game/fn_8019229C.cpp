// Calls fn_801979AC on the object's pointer at 0x14 when set, otherwise fn_8017C5A8(object, 0).

extern "C" {
struct Obj8019229C {
	unsigned char pad[0x14];
	void* f14;
};
int fn_801979AC(void*);
int fn_8017C5A8(void*, int);

int fn_8019229C(Obj8019229C* o)
{
	if (o->f14 != 0) {
		return fn_801979AC(o->f14);
	}
	return fn_8017C5A8(o, 0);
}
}
