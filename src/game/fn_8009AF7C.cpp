// Returns the 12-byte history entry i steps back from the current index (halfword at 0x3E) in a ring of 16 entries starting at 0x4C.

extern "C" {
struct Obj8009AF7C {
	unsigned char pad[0x3e];
	short s3e;
};

void* fn_8009AF7C(Obj8009AF7C* o, int i)
{
	int t = o->s3e - i;
	if (t < 0) {
		t += 0x10;
	}
	return (unsigned char*)o + t * 0xc + 0x4c;
}
}
