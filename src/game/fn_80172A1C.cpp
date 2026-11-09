// Returns the word at offset 0xac.

extern "C" {
struct Obj80172A1C {
	unsigned char pad[0xac];
	int v;
};
int fn_80172A1C(Obj80172A1C* s)
{
	return s->v;
}
}
