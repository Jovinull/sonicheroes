// Destructor: destroys the EffWink member at +0x154 and frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void __dt__7EffWinkFv(void*, int);

void* dtor_80071908(unsigned char* o, short flags)
{
	if (o != 0) {
		__dt__7EffWinkFv(o + 0x154, -1);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
