// Returns 1 when bit 1 of the flag word is clear.
struct Obj8008FE08 {
	unsigned char pad[0x18];
	unsigned f18;
};

extern "C" {
int fn_8008FE08(Obj8008FE08* o)
{
	return (unsigned int)__cntlzw(o->f18 & 2) >> 5;
}
}
