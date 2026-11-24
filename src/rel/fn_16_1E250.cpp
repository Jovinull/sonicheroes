extern "C" {
void* fn_80150588(void* model);
void fn_8015BB08(void* a, void* b);
struct Glob {
	char pad[0x725C];
	void* f725C;
};
extern Glob* lbl_8042C1D0;
struct Obj {
	char pad[0xD8];
	void* clump;
};

void fn_16_1E250(register Obj* self, void* model)
{
	self->clump = fn_80150588(model);
	fn_8015BB08(lbl_8042C1D0->f725C, self->clump);
}
}
