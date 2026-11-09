// Destructor: clears the 0x300-byte state and frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void* memset(void*, int, unsigned);

void* dtor_801247C0(void* o, short flags)
{
	if (o != 0) {
		memset(o, 0, 0x300);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
