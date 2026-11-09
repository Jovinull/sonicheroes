// Stores the two values at 0x14/0x10; when the active flag at 0xC is set, clears it and runs fn_8017C5FC with the two tables; clears 0x10C.

extern "C" {
struct Obj8017E748 {
	unsigned char pad[0xc];
	unsigned fc;
	int f10;
	int f14;
	unsigned char pad1[0x10c - 0x18];
	int f10c;
};
extern unsigned char lbl_8028F06C[];
extern unsigned char lbl_8028F0B0[];
void fn_8017C5FC(void*, void*);

void fn_8017E748(Obj8017E748* o, int a, int b)
{
	o->f14 = a;
	o->f10 = b;
	if (o->fc != 0) {
		o->fc = 0;
		fn_8017C5FC(o, lbl_8028F06C);
		fn_8017C5FC(o, lbl_8028F0B0);
	}
	o->f10c = 0;
}
}
