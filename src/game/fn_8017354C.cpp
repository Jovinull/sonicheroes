// Copies 16 bytes from the source to 0x8C of the object, sets flag 8 in the word at 8 and returns the object.

extern "C" {
void* memcpy(void*, const void*, unsigned);
struct Obj8017354C {
	unsigned char pad[8];
	unsigned f8;
	unsigned char pad1[0x8c - 0xc];
	unsigned char d[16];
};

Obj8017354C* fn_8017354C(Obj8017354C* o, const void* src)
{
	memcpy(o->d, src, 0x10);
	o->f8 |= 8;
	return o;
}
}
