// Returns the word at offset 0xa0.

extern "C" {
struct Obj80041C00 {
	unsigned char pad[0xa0];
	int v;
};
int fn_80041C00(Obj80041C00* s)
{
	return s->v;
}
}
