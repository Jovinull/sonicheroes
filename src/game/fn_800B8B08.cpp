// Calls fn_801527A4 with the object's field 0x18, the callback fn_800B8BA4 and 0, and returns the object.

extern "C" {
struct Obj800B8B08 {
	unsigned char pad[0x18];
	int f18;
};
void fn_800B8BA4();
void fn_801527A4(int, int, int);

Obj800B8B08* fn_800B8B08(Obj800B8B08* o)
{
	fn_801527A4(o->f18, (int)fn_800B8BA4, 0);
	return o;
}
}
