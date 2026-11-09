// Returns the word at offset 0x30.

extern "C" {
struct Obj80146918 {
	unsigned char pad[0x30];
	int v;
};
int fn_80146918(Obj80146918* s)
{
	return s->v;
}
}
