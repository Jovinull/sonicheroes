// Clears the field at 0xA84 and zeroes the 16-byte block at 0xAD0.

extern "C" {
void* memset(void*, int, unsigned);
struct Obj80058E20 {
	unsigned char pad[0xa84];
	int a84;
	unsigned char pad2[0xad0 - 0xa88];
	unsigned char b[1];
};

void fn_80058E20(Obj80058E20* s)
{
	s->a84 = 0;
	memset(s->b, 0, 0x10);
}
}
