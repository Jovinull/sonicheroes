// Destructor: destroys the two members at +0x1BC and +0x14C (dtor_800F1618) and frees the object when flags > 0; returns the object.

extern "C" {
void __dl__FPv(void*);
void dtor_800F1618(void*, int);

void* dtor_8003F010(unsigned char* o, short flags)
{
	if (o != 0) {
		dtor_800F1618(o + 0x1bc, -1);
		dtor_800F1618(o + 0x14c, -1);
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
