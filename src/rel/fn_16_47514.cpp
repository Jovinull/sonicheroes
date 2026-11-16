// Object callback: if fn_80226468 of the field at +0x18 is non-zero, call fn_80226440(obj, arg1); returns obj.
struct Obj47514 {
	unsigned char pad0[0x18];
	void* f18;
};

extern "C" {
unsigned fn_80226468(void*);
void fn_80226440(void*, int);

void* fn_16_47514(Obj47514* arg0, int arg1)
{
	if (fn_80226468(arg0->f18) != 0) {
		fn_80226440(arg0, arg1);
	}
	return arg0;
}
}
