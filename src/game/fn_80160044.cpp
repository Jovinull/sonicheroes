// Decodes the object's flag word into a scaled mode value: bit 0 selects 3 (set) or 2 (clear) and bits 1..3 pick a multiplier of 1, 2 or 4 (0 when out of range).

struct Obj80160044 {
	unsigned char pad0[4];
	unsigned f4;
};

extern "C" {
unsigned fn_80160044(Obj80160044* o)
{
	unsigned v = o->f4;
	unsigned r = v & 1;
	int k;
	if (r == 1) {
		r = 3;
	} else if (r == 0) {
		r = 2;
	}
	k = (v >> 1) & 7;
	switch (k) {
		case 0:
		case 1:
			return r;
		case 2:
		case 3:
			return r * 2;
		case 4:
			return r * 4;
		default:
			return 0;
	}
}
}
