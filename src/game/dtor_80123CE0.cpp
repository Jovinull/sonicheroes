// Destructor: clears the three blocks (0..8, 8..0x18, 0x18..0x58) and frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void* memset(void*, int, unsigned);

void* dtor_80123CE0(unsigned char* o, short flags)
{
	if (o != 0) {
		memset(o, 0, 8);
		memset(o + 8, 0, 0x10);
		memset(o + 0x18, 0, 0x40);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
