// Resets the active slot of lbl_803EC968 (+0x1D8): frees its list, clears the handle, marks it free and self-linked at +0x18; returns the slot.

extern "C" {
struct Slot80170428 {
	int f0;
	int f4;
	int f8;
	int fc;
	void* f10;
	void* f14;
	Slot80170428* f18;
};
struct Glob80170428 {
	unsigned char pad[0x1d4];
	int f1d4;
	Slot80170428* f1d8;
};
extern Glob80170428 lbl_803EC968;
void fn_80170FDC(void*);
void fn_80194424(int);

Slot80170428* fn_80170428(void)
{
	Slot80170428* t = lbl_803EC968.f1d8;
	fn_80170FDC(t->f14);
	t->f14 = 0;
	fn_80194424(t->f0);
	t->f8  = 0;
	t->fc  = 1;
	t->f18 = t;
	return lbl_803EC968.f1d8;
}
}
