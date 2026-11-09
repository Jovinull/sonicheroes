// If the handle at +8 is set, runs fn_802040A0 with the callback fn_80203D78, frees the handle and clears it; returns arg0.

extern "C" {
struct Obj80203E38 {
	unsigned char pad[8];
	unsigned f8;
};
void fn_80194628(unsigned);
void fn_802040A0(void*, void*, int);
extern unsigned char fn_80203D78[];

Obj80203E38* fn_80203E38(Obj80203E38* o)
{
	if (o->f8 != 0) {
		fn_802040A0(o, (void*)fn_80203D78, 0);
		fn_80194628(o->f8);
		o->f8 = 0;
	}
	return o;
}
}
