// Calls fn_80226440(object, b) when fn_80226468 of the object's field 0x18 is non-zero; returns the object.

extern "C" {
struct Obj800F3020 {
	unsigned char pad[0x18];
	int f18;
};
unsigned fn_80226468(int);
void fn_80226440(void*, int);

Obj800F3020* fn_800F3020(Obj800F3020* o, int b)
{
	if (fn_80226468(o->f18) != 0) {
		fn_80226440(o, b);
	}
	return o;
}
}
