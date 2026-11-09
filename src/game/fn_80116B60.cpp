// Sets the word at offset 0x708.

extern "C" {
struct Obj80116B60 {
	unsigned char pad[0x708];
	int v;
};
void fn_80116B60(Obj80116B60* s, int v)
{
	s->v = v;
}
}
