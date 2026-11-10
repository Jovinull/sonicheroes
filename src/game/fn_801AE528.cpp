// Flushes the entry's data when dirty and unlocks it, or raises the error report for an invalid state.
struct Arg801AE528 {
	int a;
	int b;
};
struct Obj801AE528 {
	unsigned int f0;
	unsigned char pad4[4];
	unsigned int f8;
	unsigned char padC[8];
	int f14;
	unsigned char pad18[8];
	unsigned char f20;
	unsigned char pad21;
	unsigned char f22;
};

extern "C" {
extern int lbl_8042CA48;
int fn_8019408C(int a, ...);
void fn_80193FE8(Arg801AE528* p);
void DCFlushRange(void* p, int n);

int fn_801AE528(int unused, Obj801AE528* o)
{
	Arg801AE528 sp;
	switch (o->f20 & 7) {
		case 4:
		case 0:
			if ((unsigned int)o == o->f0) {
				char* p = (char*)o + lbl_8042CA48;
				if (o->f22 & 0x10) {
					DCFlushRange(*(void**)(p + 0x20), (1 << o->f14) * 2);
				}
				o->f22 = o->f22 & ~0x18;
				o->f8  = 0;
			}
			return 1;
		default:
		case 3:
		case 5:
			sp.a = 1;
			sp.b = fn_8019408C(0x80000011);
			fn_80193FE8(&sp);
			return 0;
	}
}
}
