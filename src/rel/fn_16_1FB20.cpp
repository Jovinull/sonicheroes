extern "C" void __dl__FPv(void* memory);
struct S {
	char pad[0xF8];
	void* buf;
};
extern "C" void fn_16_1FB20(register S* obj)
{
	if (obj->buf != 0) {
		__dl__FPv(obj->buf);
		obj->buf = 0;
	}
}
