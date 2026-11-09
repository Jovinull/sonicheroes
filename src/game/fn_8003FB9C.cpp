// Calls fn_8015C878 with the object's field 0x18 and the table lbl_802AD0F0, and returns the object.

extern "C" {
struct Obj8003FB9C {
	unsigned char pad[0x18];
	int f18;
};
extern unsigned char lbl_802AD0F0[];
void fn_8015C878(int, int);

Obj8003FB9C* fn_8003FB9C(Obj8003FB9C* o)
{
	fn_8015C878(o->f18, (int)lbl_802AD0F0);
	return o;
}
}
