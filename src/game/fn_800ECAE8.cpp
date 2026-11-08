// Returns the word at offset 0x2c.

extern "C" {
struct Obj800ECAE8 {
	unsigned char pad[0x2c];
	int v;
};
int fn_800ECAE8(Obj800ECAE8* s)
{
	return s->v;
}
}
