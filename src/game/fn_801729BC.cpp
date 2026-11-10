// Runs the global handler callback at +0x138 on the object's id and, when a second handle is set, returns fn_80169EF4's result (else 1).
struct Cb801729BC {
	unsigned char pad0[0x138];
	void (*f138)(int a, Cb801729BC* self);
};
struct Obj801729BC {
	unsigned char pad0[0xAC];
	int fAC;
	unsigned int fB0;
};

extern "C" {
extern Cb801729BC* lbl_8042C9A4;
int fn_80169EF4(unsigned int a);

int fn_801729BC(Obj801729BC* o)
{
	int r = 1;
	lbl_8042C9A4->f138(o->fAC, lbl_8042C9A4);
	if (o->fB0 != 0) {
		r = fn_80169EF4(o->fB0);
	}
	return r;
}
}
