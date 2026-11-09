// Allocates a block sized from the object's 0x1AC/0x1A8 fields (fn_8017CC54), initialises it with fn_8017BFD4 when allocated, and returns it (0 for a null object).

extern "C" {
struct Obj8017BF7C {
	unsigned char pad[0x1a8];
	int f1a8;
	int f1ac;
};
unsigned fn_8017CC54(int, int, int);
void fn_8017BFD4(unsigned*, int);

unsigned fn_8017BF7C(Obj8017BF7C* o)
{
	unsigned sp8;
	if (o == 0) {
		return 0;
	}
	sp8 = fn_8017CC54(2, o->f1ac, o->f1a8);
	if (sp8 != 0) {
		fn_8017BFD4(&sp8, 0x120);
	}
	return sp8;
}
}
