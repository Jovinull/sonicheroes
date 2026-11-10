// Copies entry idx of the object's 12-byte record list into out and returns it; reports an invalid-argument error (and returns 0) when idx is negative or out of range for the object's mode (1 or 2).
struct Rec8014D208 {
	unsigned char b[12];
};
struct Err8014D208 {
	int a;
	int b;
};
struct Obj8014D208 {
	unsigned char pad0[8];
	int f8;
	int fC;
	unsigned char pad10[4];
	Rec8014D208* f14;
};

extern "C" {
extern char lbl_8028D210[];
void fn_80193FE8(Err8014D208* e);
int fn_8019408C(unsigned int code, ...);

Rec8014D208* fn_8014D208(Obj8014D208* o, int idx, Rec8014D208* out)
{
	Err8014D208 e2;
	Err8014D208 e1;
	int n;
	if (idx >= 0) {
		switch (o->fC) {
			case 1:
				n = o->f8 - 2;
				break;
			case 2:
				n = o->f8 - 3;
				break;
			default:
				e1.a = 0x102;
				e1.b = fn_8019408C(1);
				fn_80193FE8(&e1);
				n = 0;
				break;
		}
		if (idx < n) {
			Rec8014D208* src = o->f14 + idx;
			*out             = *src;
			return out;
		}
	}
	e2.a = 0x102;
	e2.b = fn_8019408C(0x80000003, lbl_8028D210);
	fn_80193FE8(&e2);
	return 0;
}
}
