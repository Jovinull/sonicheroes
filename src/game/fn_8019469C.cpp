// Returns the word at offset 0x4.

extern "C" {
struct Obj8019469C {
	unsigned char pad[0x4];
	int v;
};
int fn_8019469C(Obj8019469C* s)
{
	return s->v;
}
}
