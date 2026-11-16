struct Inner {
	char pad[0x100];
	int mode;
	char a[0xC];
	char b[1];
};
struct Obj {
	char pad[0x28];
	char c[0x88];
	Inner* in;
};
extern "C" void fn_16_1EB9C(Obj*);
extern "C" void fn_16_1180(void*, void*, void*);
extern "C" void fn_16_1EE18(register Obj* self)
{
	if (self->in->mode != 5) {
		fn_16_1EB9C(self);
		fn_16_1180(self->c, self->in->a, self->in->b);
	}
}
