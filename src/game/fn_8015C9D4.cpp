// Creates and registers a new object in the manager's slot table; returns 1 on success.
struct Obj8015C9D4 {
	unsigned char pad0[0x2C];
	int f2C;
};

extern "C" {
extern int lbl_8042C9A4;
extern int lbl_8042CA80;
void fn_8015BF04(Obj8015C9D4* o, int a, int b);
int fn_8015D898();
Obj8015C9D4* fn_801B3984();
void fn_801B3A10(Obj8015C9D4* o);
unsigned int fn_801B43EC();
int fn_801B4EB4();
void fn_801B52BC(int a, int b, int c, int d, ...);

int fn_8015C9D4()
{
	Obj8015C9D4* o;
	int h;
	o = fn_801B3984();
	if (o != 0) {
		o->f2C = 2;
		h      = fn_801B4EB4();
		if (h != 0) {
			fn_801B52BC(h, 0, fn_8015D898(), 0);
			if (fn_801B43EC() != 0) {
				int a                              = lbl_8042CA80;
				int b                              = lbl_8042C9A4;
				((Obj8015C9D4**)(b + a))[0x58 / 4] = o;
				fn_8015BF04(o, a, b);
				return 1;
			}
		}
		fn_801B3A10(o);
	}
	return 0;
}
}
