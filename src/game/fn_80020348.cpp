// Sets the two low bits of byte 3 of entry i (0x30 bytes each) of the table at 0x10 to the low bits of v.

extern "C" {
struct Entry80020348 {
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
	unsigned char pad[0x2c];
};
struct Obj80020348 {
	unsigned char pad[0x10];
	Entry80020348* table;
};

void fn_80020348(Obj80020348* s, int i, int v)
{
	Entry80020348* e = s->table + i;
	e->b3            = (e->b3 & ~3) | (v & 3);
}
}
