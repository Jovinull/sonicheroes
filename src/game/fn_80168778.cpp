// Returns 0x14 + (count - 1) * 8 for the byte count at +0x1C.

extern "C" {
struct Obj80168778 {
	unsigned char pad[0x1c];
	unsigned char c1c;
};

int fn_80168778(Obj80168778* o)
{
	return (o->c1c - 1) * 8 + 0x14;
}
}
