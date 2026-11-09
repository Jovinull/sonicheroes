// Returns the word at offset 0xcc.

extern "C" {
struct Obj8012491C {
	unsigned char pad[0xcc];
	int v;
};
int fn_8012491C(Obj8012491C* s)
{
	return s->v;
}
}
