// Returns the low two bits of the byte at +3 of the record held at +0xA0.

extern "C" {
struct Flags8019E334 {
	unsigned char pad[3];
	unsigned char c3;
};
struct Obj8019E334 {
	unsigned char pad[0xa0];
	Flags8019E334* fa0;
};

int fn_8019E334(Obj8019E334* o)
{
	return o->fa0->c3 & 3;
}
}
