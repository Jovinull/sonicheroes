// Returns the signed byte at 0x190, first calling fn_800A6334 when it is -1.

extern "C" {
struct Obj800A5844 {
	unsigned char pad[0x190];
	signed char c190;
};
void fn_800A6334(Obj800A5844*);

int fn_800A5844(Obj800A5844* o)
{
	if (o->c190 == -1) {
		fn_800A6334(o);
	}
	return o->c190;
}
}
