// Sets flag bits 0x4000 in the word at offset 0x30.

extern "C" {
struct Obj8017E7D0 {
	unsigned char pad[0x30];
	unsigned int v;
};
void fn_8017E7D0(Obj8017E7D0* s)
{
	s->v |= 0x4000;
}
}
