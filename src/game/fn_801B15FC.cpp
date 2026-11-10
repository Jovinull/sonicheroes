// Computes the size needed for the header and its entries.
struct Hdr801B15FC {
	unsigned char pad0[0x14];
	int f14;
	unsigned char pad18[0xB];
	unsigned char f23;
};

extern "C" {
int fn_801AD750(Hdr801B15FC* h);

int fn_801B15FC(int* out, Hdr801B15FC** hp)
{
	int n;
	Hdr801B15FC* h = *hp;
	if (h == 0) {
		*out = 0x64;
		return 1;
	}
	n = 0x74;
	if ((h->f23 << 8) & 0x6000) {
		n = (1 << h->f14) * 2 + 0x74;
	}
	n += 4;
	n += fn_801AD750(h);
	*out = n;
	return 1;
}
}
