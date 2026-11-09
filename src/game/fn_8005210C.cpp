// Frees the object (operator delete) when it is non-null and the flags are positive; returns the object.

extern "C" {
void __dl__FPv(void*);

void* fn_8005210C(void* p, short flags)
{
	if (p != 0 && flags > 0) {
		__dl__FPv(p);
	}
	return p;
}
}
