// Runs fn_80155E70 on the object's second block (+0x20), stores its result at +0x54 and returns arg0 only when that result is non-zero.

extern "C" {
struct Obj8015B33C {
	unsigned char pad[0x54];
	unsigned f54;
};
unsigned fn_80155E70(void*, void*, void*);

void* fn_8015B33C(void* a, int unused, Obj8015B33C* o)
{
	o->f54 = fn_80155E70(a, o, (unsigned char*)o + 0x20);
	if (o->f54 != 0) {
		return a;
	}
	return 0;
}
}
