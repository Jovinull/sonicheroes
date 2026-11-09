// Refreshes the cached counters in lbl_803E774C from the global state.
struct S803E774C {
	unsigned char pad0[0x22];
	unsigned char f22;
	unsigned char pad23;
	signed char f24;
	signed char f25;
	unsigned char pad26[2];
	int f28;
	int f2C;
};
struct S8042C180 {
	unsigned char pad0[0x2C];
	int f2C;
	unsigned char pad30[8];
	int f38;
};
struct S8029C310 {
	unsigned char pad0[0x2C];
	int f2C;
	unsigned char pad30[0x20C];
	int f23C;
};

extern "C" {
extern S803E774C lbl_803E774C;
extern S8042C180* lbl_8042C180;
extern S8029C310 lbl_8029C310;
int fn_80117148(void* p);
void fn_80019830(S8029C310* p);

void fn_80116B84()
{
	lbl_803E774C.f22 = (unsigned char)fn_80117148((char*)&lbl_803E774C + 0x3C);
	int v            = lbl_8042C180->f2C;
	if (v < 0) {
		v = 0x7FFFFFFF;
	}
	unsigned int t   = v / 60;
	lbl_803E774C.f2C = t;
	if (lbl_803E774C.f22 < 0x78) {
		lbl_803E774C.f28 = t;
	}
	if (lbl_8042C180->f38 == 2) {
		lbl_803E774C.f24 = lbl_8029C310.f23C;
		lbl_803E774C.f25 = lbl_8029C310.f2C;
	}
	fn_80019830(&lbl_8029C310);
}
}
