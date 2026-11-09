// Zeroes 0x300 bytes at the given address and returns it.

extern "C" {
void* memset(void*, int, unsigned);

void* fn_80124820(void* a)
{
	memset(a, 0, 0x300);
	return a;
}
}
