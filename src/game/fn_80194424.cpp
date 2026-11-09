// Stores 0 at offset 0x4.

extern "C" {
struct Obj80194424 {
	unsigned char pad[0x4];
	int v;
};
void fn_80194424(Obj80194424* s)
{
	s->v = 0;
}
}
