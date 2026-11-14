// Shuts an object down: fn_801B2EF0(0, k) for k = 3, 5, 4, 1, 2, then releases the handle at 0x00
// (fn_801B3A10) when set and clears the five words at 0x00.
struct Obj801B802C {
	void* f0;
	int f4;
	int f8;
	int fC;
	int f10;
};

extern "C" {
void fn_801B2EF0(int a, int k);
void fn_801B3A10(void* h);

void fn_801B802C(Obj801B802C* o)
{
	fn_801B2EF0(0, 3);
	fn_801B2EF0(0, 5);
	fn_801B2EF0(0, 4);
	fn_801B2EF0(0, 1);
	fn_801B2EF0(0, 2);
	if (o->f0 != 0) {
		fn_801B3A10(o->f0);
	}
	o->f0  = 0;
	o->f4  = 0;
	o->f8  = 0;
	o->fC  = 0;
	o->f10 = 0;
}
}
