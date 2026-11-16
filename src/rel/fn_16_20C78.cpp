extern "C" int fn_80150588(int);
struct S {
	char pad[0xF4];
	int f4;
};
extern "C" void fn_16_20C78(register S* self, int a)
{
	self->f4 = fn_80150588(a);
}
