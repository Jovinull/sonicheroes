// Sets the byte at offset 0x1c.

extern "C" {
struct Obj80169D58 {
	unsigned char pad[0x1c];
	unsigned char v;
};
void fn_80169D58(Obj80169D58* s, int v)
{
	s->v = v;
}
}
