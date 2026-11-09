// Forwards the block from fn_80159698 (and +0x10 of it) together with the handle at +0x80 and arg0 to fn_80155C6C.

extern "C" {
struct Obj8015B4D0 {
	unsigned char pad[0x80];
	int f80;
};
void* fn_80159698(void*);
void fn_80155C6C(int, void*, int, void*);

void fn_8015B4D0(int a, int unused, Obj8015B4D0* o)
{
	void* t = fn_80159698(o);
	fn_80155C6C(o->f80, t, a, (unsigned char*)t + 0x10);
}
}
