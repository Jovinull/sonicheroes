// Calls fn_801527A4 with the object's field 0x18, the callback fn_800BDFC8 and 0, and returns the object.

extern "C" {
struct Obj800BDF5C {
	unsigned char pad[0x18];
	int f18;
};
void fn_800BDFC8();
void fn_801527A4(int, int, int);

Obj800BDF5C* fn_800BDF5C(Obj800BDF5C* o)
{
	fn_801527A4(o->f18, (int)fn_800BDFC8, 0);
	return o;
}
}
