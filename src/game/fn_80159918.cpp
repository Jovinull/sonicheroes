// Returns the word at offset 0x68.

extern "C" {
struct Obj80159918 {
	unsigned char pad[0x68];
	int v;
};
int fn_80159918(Obj80159918* s)
{
	return s->v;
}
}
