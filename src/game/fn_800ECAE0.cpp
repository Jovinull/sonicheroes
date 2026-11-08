// Returns the halfword at offset 0x206.

extern "C" {
struct Obj800ECAE0 {
	unsigned char pad[0x206];
	short v;
};
short fn_800ECAE0(Obj800ECAE0* s)
{
	return s->v;
}
}
