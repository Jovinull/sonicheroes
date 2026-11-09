// Allocates a.b bytes with fn_8017CDA4 and zero-fills them (in two memset calls above 0x8000 bytes); returns the block.

extern "C" {
int fn_8017CDA4(int, unsigned);
void* memset(void*, int, unsigned);

unsigned char* fn_8017BE30(int unused, int a, int b)
{
	unsigned n       = a * b;
	unsigned char* p = (unsigned char*)fn_8017CDA4(unused, n);
	if (n > 0x8000) {
		memset(p, 0, 0x8000);
		memset(p + 0x8000, 0, n - 0x8000);
	} else {
		memset(p, 0, n);
	}
	return p;
}
}
