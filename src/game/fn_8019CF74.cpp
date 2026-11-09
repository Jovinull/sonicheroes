// Returns the object when fn_801A18A4 accepts its field 0x60, otherwise 0.

extern "C" {
struct Obj8019CF74 {
	unsigned char pad[0x60];
	int f60;
};
unsigned fn_801A18A4(int);

Obj8019CF74* fn_8019CF74(Obj8019CF74* o)
{
	if (fn_801A18A4(o->f60) != 0) {
		return o;
	}
	return 0;
}
}
