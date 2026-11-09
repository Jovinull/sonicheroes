// Returns the word at offset 0xb0.

extern "C" {
struct Obj80173A44 {
	unsigned char pad[0xb0];
	int v;
};
int fn_80173A44(Obj80173A44* s)
{
	return s->v;
}
}
