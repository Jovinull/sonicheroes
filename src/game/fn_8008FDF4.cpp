// Returns whether neither flag 0x8000 nor 2 of the word at 0x18 is set.

extern "C" {
struct Obj8008FDF4 {
	unsigned char pad[0x18];
	unsigned f18;
};

int fn_8008FDF4(Obj8008FDF4* o)
{
	return (o->f18 & 0x8002) == 0 ? 1 : 0;
}
}
