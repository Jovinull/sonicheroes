// Destructor: destroys the member at +0x148 and the EffWink members at +0x120 and +0xF8, then frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void __dt__7EffWinkFv(void*, int);
void dtor_800F1618(void*, int);

void* dtor_8007C02C(unsigned char* o, short flags)
{
	if (o != 0) {
		dtor_800F1618(o + 0x148, -1);
		__dt__7EffWinkFv(o + 0x120, -1);
		__dt__7EffWinkFv(o + 0xf8, -1);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
