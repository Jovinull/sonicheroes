// Swaps the four bytes of every word of a buffer of `size` bytes in place; returns the buffer.
typedef unsigned int u32;
typedef unsigned char u8;

extern "C" {
void* fn_80193270(void* mem, unsigned int size)
{
	u32* p = (u32*)mem;
	size >>= 2;
	while (size--) {
		*p = (*p >> 24) | ((*p >> 8) & 0xff00) | ((*p << 8) & 0xff0000) | (*p << 24);
		p++;
	}
	return mem;
}
}
