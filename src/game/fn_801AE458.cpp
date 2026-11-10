// Marks the entry as locked and returns its data pointer, or raises the error report for an invalid state.
struct Arg801AE458 {
	int a;
	int b;
};
struct Obj801AE458 {
	unsigned int f0;
	unsigned char pad4[4];
	unsigned int f8;
	unsigned char padC[0x14];
	unsigned char f20;
	unsigned char pad21;
	unsigned char f22;
};

extern "C" {
extern int lbl_8042CA48;
int fn_8019408C(int a, ...);
void fn_80193FE8(Arg801AE458* p);

int fn_801AE458(unsigned int* out, Obj801AE458* o, int flags)
{
	Arg801AE458 sp;
	switch (o->f20 & 7) {
		case 4:
		case 0:
			if ((unsigned int)o == o->f0 && o->f8 == 0) {
				char* p = (char*)o + lbl_8042CA48;
				if (flags & 2) {
					o->f22 = o->f22 | 8;
				}
				if (flags & 1) {
					o->f22 = o->f22 | 0x10;
				}
				o->f8 = *(unsigned int*)(p + 0x20);
				*out  = o->f8;
			}
			return 1;
		default:
		case 3:
		case 5:
			sp.a = 1;
			sp.b = fn_8019408C(0x8000000E);
			fn_80193FE8(&sp);
			return 0;
	}
}
}
