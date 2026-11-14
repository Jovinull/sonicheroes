// Clears the 0x120-byte buffer of an object, first replacing it (fn_8017CD30 releases the old
// one, fn_8017CC2C(2) gets the new one) when the given capacity is below 0x120.
struct Obj8017BFD4 {
	void* buffer;
};

extern "C" {
void* memset(void* dst, int value, unsigned long n);
void fn_8017CD30(void* p);
void* fn_8017CC2C(int kind);

void fn_8017BFD4(Obj8017BFD4* o, unsigned int capacity)
{
	void* p = o->buffer;
	if (capacity < 0x120) {
		fn_8017CD30(p);
		o->buffer = p = fn_8017CC2C(2);
	}
	memset(p, 0, 0x120);
}
}
