// Stores 0 at offset 0x28.

extern "C" {
struct Obj8001EECC {
	unsigned char pad[0x28];
	int v;
};
void fn_8001EECC(Obj8001EECC* s)
{
	s->v = 0;
}
}
