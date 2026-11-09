// Calls fn_8015C878 with the object's field 0x18 and the table lbl_803E71B4, and returns the object.

extern "C" {
struct Obj800FD298 {
	unsigned char pad[0x18];
	int f18;
};
extern unsigned char lbl_803E71B4[];
void fn_8015C878(int, int);

Obj800FD298* fn_800FD298(Obj800FD298* o)
{
	fn_8015C878(o->f18, (int)lbl_803E71B4);
	return o;
}
}
