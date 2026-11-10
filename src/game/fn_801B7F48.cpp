// Creates and registers a new object, storing it through the out pointer on success.
struct Obj801B7F48 {
	unsigned char pad0[0x2C];
	int f2C;
};

extern "C" {
void fn_801B2EA0();
Obj801B7F48* fn_801B3984();
void fn_801B3A10(Obj801B7F48* o);
Obj801B7F48* fn_801B43EC();
int fn_801B4EB4();
void fn_801B52BC(int a, int b, int c, int d, ...);
int fn_801B81A8();

int fn_801B7F48(Obj801B7F48** out)
{
	Obj801B7F48* o;
	int h;
	o = fn_801B3984();
	if (o != 0) {
		o->f2C = 1;
		h      = fn_801B4EB4();
		if (h != 0) {
			fn_801B52BC(h, 0, fn_801B81A8(), 0);
			o = fn_801B43EC();
			if (o != 0) {
				*out = o;
				fn_801B2EA0();
				return 1;
			}
		}
		fn_801B3A10(o);
	}
	return 0;
}
}
