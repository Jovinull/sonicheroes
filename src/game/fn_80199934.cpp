// Carves a 32-byte aligned free block out of the buffer a (size n) and links it as the first/last entry; returns 0 when less than 0x20 bytes remain.

extern "C" {
struct Block80199934 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
};

int fn_80199934(int a, int n)
{
	int s  = (a + 0x27) & ~0x1f;
	int sz = (((a + n) & ~0x1f) - s) - 0x20;
	Block80199934* b;
	if (sz < 0x20) {
		return 0;
	}
	b            = (Block80199934*)s;
	b->f0        = a;
	b->f4        = 0;
	b->f8        = 0;
	b->f10       = 0;
	b->fc        = sz;
	((int*)a)[0] = s;
	((int*)a)[1] = s;
	return 1;
}
}
