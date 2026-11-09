// Calls fn_80137D0C with the second argument and the two signed bytes at 0x761 and 0x760 of the first.

extern "C" {
struct Obj800469CC {
	unsigned char pad[0x760];
	signed char c760;
	signed char c761;
};
void fn_80137D0C(int, int, int);

void fn_800469CC(Obj800469CC* o, int b)
{
	fn_80137D0C(b, o->c761, o->c760);
}
}
