// Swaps the two bytes of every halfword of a buffer of `size` bytes in place; returns the buffer.
extern "C" {
void* fn_801932E0(void* mem, unsigned int size)
{
	unsigned short* p = (unsigned short*)mem;
	size >>= 1;
	while (size--) {
		*p = (*p >> 8) | (*p << 8);
		p++;
	}
	return mem;
}
}
