// Sets the byte at offset 0xa.

extern "C" {
struct Obj8015C720 {
	unsigned char pad[0xa];
	unsigned char v;
};
void fn_8015C720(Obj8015C720* s, int v)
{
	s->v = v;
}
}
