// Reads a big-endian 32-bit value from four bytes.

extern "C" {
struct Bytes80185F40 {
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
};

int fn_80185F40(Bytes80185F40* p)
{
	return (p->b0 << 24) + (p->b1 << 16) + (p->b2 << 8) + p->b3;
}
}
