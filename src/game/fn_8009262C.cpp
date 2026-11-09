// Returns the 16-byte entry `i` (0-9) at 0x15C of the object, or 0 for an index out of range.

extern "C" {
void* fn_8009262C(int a, int i)
{
	if (i >= 0xa) {
		return 0;
	}
	return (void*)(a + i * 0x10 + 0x15c);
}
}
