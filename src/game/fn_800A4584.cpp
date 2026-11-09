// Returns the largest (signed, at least 0) of the eight bytes at 0x191..0x198.

extern "C" {
struct Obj800A4584 {
	unsigned char pad[0x191];
	signed char c[8];
};

int fn_800A4584(Obj800A4584* o)
{
	int m = 0;
	int i;
	for (i = 0; i < 8; i++) {
		if (m < o->c[i]) {
			m = o->c[i];
		}
	}
	return m;
}
}
