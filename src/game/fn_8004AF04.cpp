// Moves the 0x40-byte block at 0x388 to 0x3C8 and clears the original.

extern "C" {
void* memcpy(void*, const void*, unsigned);
void* memset(void*, int, unsigned);

void fn_8004AF04(unsigned char* o)
{
	memcpy(o + 0x3c8, o + 0x388, 0x40);
	memset(o + 0x388, 0, 0x40);
}
}
