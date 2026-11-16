class C_COLLI
{
public:
	void CalcRange();
};

struct Inner {
	char pad0[0x28];
	int f28;
	int f2C;
};

struct Obj {
	char pad0[0x30];
	C_COLLI colli;
	char pad1[0x40 - 0x30 - 1];
	Inner* p40;
	char pad2[0xD4 - 0x44];
	int fD4;
};

extern "C" void fn_16_A960(Obj* self)
{
	if (self->p40 != 0) {
		self->p40->f28 = 0x4000;
		self->p40->f2C = self->fD4 - 0x1200;
		self->colli.CalcRange();
	}
}
