// Sets flag bits 0x2 in the word at offset 0x8.

extern "C" {
struct Obj8017348C {
	unsigned char pad[0x8];
	unsigned int v;
};
void fn_8017348C(Obj8017348C* s)
{
	s->v |= 0x2;
}
}
