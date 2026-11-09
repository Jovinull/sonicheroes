// Sums the sizes of the entry's children plus the optional extra block.
struct Ent80146214 {
	unsigned char pad0[4];
	unsigned int f4;
	int f8;
	unsigned char padC[0x24];
	unsigned int f30;
};

extern "C" {
int fn_80147F64(int a);
int fn_8019A588(int a);

int fn_80146214(int a, int b)
{
	int* p;
	Ent80146214* h;
	int total;
	unsigned int i;
	total = 0;
	h     = *(Ent80146214**)(a + b);
	if (h != 0) {
		p     = (int*)h;
		i     = 0;
		total = h->f4 + 8;
		for (; i < h->f4; i++) {
			total += fn_80147F64(p[2]);
			p++;
		}
		if (h->f30 != 0) {
			int e = fn_8019A588(h->f30 + 8);
			total = e + total;
			total += 0xC;
		}
	}
	return total;
}
}
