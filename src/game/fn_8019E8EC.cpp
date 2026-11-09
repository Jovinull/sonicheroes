// If the record at +0xA0 has its bit 0 set at +3, runs fn_801A3178 on it; returns the sub-object at +0x50.

extern "C" {
struct Flags8019E8EC {
	unsigned char pad[3];
	unsigned char c3;
};
struct Obj8019E8EC {
	unsigned char pad[0x50];
	unsigned char sub[1];
	unsigned char pad1[0x4f];
	Flags8019E8EC* fa0;
};
void fn_801A3178(void*);

unsigned char* fn_8019E8EC(Obj8019E8EC* o)
{
	if (o->fa0->c3 & 1) {
		fn_801A3178(o->fa0);
	}
	return o->sub;
}
}
