// Runs fn_8013D324 on the object when fn_8013CC34 accepts its field 0x18; returns 1.

extern "C" {
struct Obj8013D274 {
	unsigned char pad[0x18];
	int f18;
};
unsigned fn_8013CC34(int);
void fn_8013D324(void*);

int fn_8013D274(Obj8013D274* o)
{
	if (fn_8013CC34(o->f18) != 0) {
		fn_8013D324(o);
	}
	return 1;
}
}
