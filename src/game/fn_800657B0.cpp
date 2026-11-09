// Points the object's field 0x54 at lbl_80243BF8, calls fn_80065558 on the object and returns it.

extern "C" {
struct Obj800657B0 {
	unsigned char pad[0x54];
	void* f54;
};
extern unsigned char lbl_80243BF8[];
void fn_80065558(Obj800657B0*, int);

Obj800657B0* fn_800657B0(Obj800657B0* o, int b)
{
	o->f54 = lbl_80243BF8;
	fn_80065558(o, b);
	return o;
}
}
