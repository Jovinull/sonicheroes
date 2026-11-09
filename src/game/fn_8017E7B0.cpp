// Sets flag bits 0x400 in the word at offset 0x30.

extern "C" {
struct Obj8017E7B0 {
	unsigned char pad[0x30];
	unsigned int v;
};
void fn_8017E7B0(Obj8017E7B0* s)
{
	s->v |= 0x400;
}
}
