// Stores 1 at offset 0xb8.

extern "C" {
struct Obj80174420 {
	unsigned char pad[0xb8];
	int v;
};
void fn_80174420(Obj80174420* s)
{
	s->v = 1;
}
}
