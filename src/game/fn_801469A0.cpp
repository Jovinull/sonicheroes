// Stores a byte into the entry at the given index and returns the base pointer.
extern "C" {
unsigned char* fn_801469A0(unsigned char* a, int b, unsigned char c)
{
	(a + b)[0x28] = c;
	return a;
}
}
