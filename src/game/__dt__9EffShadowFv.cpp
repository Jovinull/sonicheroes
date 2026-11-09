// Destructor (EffShadow): releases the handle at +0x28 (clearing +0x20 and releasing +0x24) and the one at +0x2C, then frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void fn_801A491C(unsigned);
void fn_801A173C(unsigned);
void fn_8019E480(unsigned);
struct Shadow9EffShadow {
	unsigned char pad[0x20];
	int f20;
	unsigned f24;
	unsigned f28;
	unsigned f2c;
};

Shadow9EffShadow* __dt__9EffShadowFv(Shadow9EffShadow* o, short flags)
{
	if (o != 0) {
		if (o->f28 != 0) {
			fn_801A491C(o->f28);
			o->f28 = 0;
			o->f20 = 0;
			if (o->f24 != 0) {
				fn_801A173C(o->f24);
			}
			o->f24 = 0;
		}
		if (o->f2c != 0) {
			fn_8019E480(o->f2c);
			o->f2c = 0;
		}
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
