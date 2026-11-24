extern "C" void fn_80150958(void* clump);

struct S {
	char pad[0xF4];
	void* clump;
};

extern "C" void fn_16_20C34(register S* self)
{
	if (self->clump) {
		fn_80150958(self->clump);
		self->clump = 0;
	}
}
