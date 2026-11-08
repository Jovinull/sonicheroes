// Sets the byte at offset 0x3f.

extern "C" {
struct Obj80136C24 {
	unsigned char pad[0x3f];
	unsigned char v;
};
void fn_80136C24(Obj80136C24* s, int v)
{
	s->v = v;
}
}
