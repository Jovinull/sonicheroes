// Returns the word at offset 0x4.

extern "C" {
struct Obj801468B4 {
	unsigned char pad[0x4];
	int v;
};
int fn_801468B4(Obj801468B4* s)
{
	return s->v;
}
}
