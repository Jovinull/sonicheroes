// Destructor: frees the array held at +4, then the object itself when flags > 0; returns the object.

extern "C" {
void __dla__FPv(void*);
void __dl__FPv(void*);
struct Obj80126790 {
	unsigned char pad[4];
	void* f4;
};

Obj80126790* fn_80126790(Obj80126790* o, short flags)
{
	if (o != 0) {
		if (o->f4 != 0) {
			__dla__FPv(o->f4);
		}
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
