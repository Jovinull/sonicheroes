// Returns the word at offset 0x24.

extern "C" {
struct Obj802043AC {
	unsigned char pad[0x24];
	int v;
};
int fn_802043AC(Obj802043AC* s)
{
	return s->v;
}
}
