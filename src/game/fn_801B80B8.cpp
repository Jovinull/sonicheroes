// Builds the five-slot sound/camera holder: allocates the base object and the list entry, fills all five handles with the new object and applies the five mode setups; releases the object and returns 0 on failure.
struct Obj801B80B8 {
	unsigned char pad0[0x2C];
	int f2C;
};
struct Holder801B80B8 {
	Obj801B80B8* f0;
	Obj801B80B8* f4;
	Obj801B80B8* f8;
	Obj801B80B8* fC;
	Obj801B80B8* f10;
};

extern "C" {
Obj801B80B8* fn_801B3984();
void fn_801B3A10(Obj801B80B8* o);
Obj801B80B8* fn_801B43EC();
int fn_801B4EB4();
void fn_801B52BC(int a, int b, int c, int d, ...);
int fn_801B8DFC();
void fn_801B2EF0(Obj801B80B8* o, int mode);

int fn_801B80B8(Holder801B80B8* h)
{
	Obj801B80B8* o;
	int t;
	o = fn_801B3984();
	if (o != 0) {
		o->f2C = 1;
		t      = fn_801B4EB4();
		if (t != 0) {
			fn_801B52BC(t, 0, fn_801B8DFC(), 0);
			o = fn_801B43EC();
			if (o != 0) {
				h->f0  = o;
				h->f4  = o;
				h->f8  = o;
				h->fC  = o;
				h->f10 = o;
				fn_801B2EF0(o, 3);
				fn_801B2EF0(o, 5);
				fn_801B2EF0(o, 4);
				fn_801B2EF0(o, 1);
				fn_801B2EF0(o, 2);
				return 1;
			}
		}
		fn_801B3A10(o);
	}
	return 0;
}
}
