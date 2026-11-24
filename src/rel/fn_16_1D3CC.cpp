extern "C" void __dl__FPv(void*);
struct S {
	char pad[0xDC];
	void* p;
};
extern "C" void fn_16_1D3CC(register S* self)
{
	if (self->p != 0) {
		__dl__FPv(self->p);
		self->p = 0;
	}
}
