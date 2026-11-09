// Sets the word at offset 0x4.

extern "C" {
struct Obj80173614 {
	unsigned char pad[0x4];
	int v;
};
void fn_80173614(Obj80173614* s, int v)
{
	s->v = v;
}
}
