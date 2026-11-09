// Calls fn_801A4B3C(p, object) when p is non-null; returns the object.

extern "C" {
void fn_801A4B3C(void*, void*);

void* fn_8006637C(void* o, void* p)
{
	if (p != 0) {
		fn_801A4B3C(p, o);
	}
	return o;
}
}
