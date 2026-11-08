// Returns the word at offset 0x8.

extern "C" {
struct Obj8013F47C {
	unsigned char pad[0x8];
	int v;
};
int fn_8013F47C(Obj8013F47C* s)
{
	return s->v;
}
}
