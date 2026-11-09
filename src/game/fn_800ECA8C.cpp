// Returns the word at offset 0x4.

extern "C" {
struct Obj800ECA8C {
	unsigned char pad[0x4];
	int v;
};
int fn_800ECA8C(Obj800ECA8C* s)
{
	return s->v;
}
}
