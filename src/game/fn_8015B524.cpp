// Runs fn_80155E70 on the block returned by fn_80159698 (and +0x10 of it), stores the result at +0x80 and returns arg0 only when it is non-zero.

extern "C" {
struct Obj8015B524 {
	unsigned char pad[0x80];
	unsigned f80;
};
void* fn_80159698(void*);
unsigned fn_80155E70(void*, void*, void*);

void* fn_8015B524(void* a, int unused, Obj8015B524* o)
{
	void* t = fn_80159698(o);
	o->f80  = fn_80155E70(a, t, (unsigned char*)t + 0x10);
	if (o->f80 != 0) {
		return a;
	}
	return 0;
}
}
