// Starts the handler fn_8003C6FC on the handle at +0x18 and, when it reports 1, either switches state with fn_80226580(o, 2) or runs fn_801491A8 depending on fn_80226468; returns arg0.

extern "C" {
struct Obj8003C66C {
	unsigned char pad[0x18];
	unsigned f18;
};
unsigned fn_801527A4(unsigned, void*, int*);
unsigned fn_80226468(unsigned);
void fn_80226580(void*, int);
void fn_801491A8(void*);
extern unsigned char fn_8003C6FC[];

Obj8003C66C* fn_8003C66C(Obj8003C66C* o)
{
	int sp8    = 0;
	unsigned t = o->f18;
	if (t != 0) {
		fn_801527A4(t, fn_8003C6FC, &sp8);
		if (sp8 == 1) {
			if (fn_80226468(t) != 0) {
				fn_80226580(o, 2);
			} else {
				fn_801491A8(o);
			}
		}
	}
	return o;
}
}
