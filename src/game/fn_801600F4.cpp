// Maps the 3-bit field of +4 selected by arg1 (shift 14 + 4*arg1) to a count: {0,3} -> 2, {1,4} -> 3, {2,5} -> 4, else 0.

extern "C" {
struct Obj801600F4 {
	unsigned char pad[4];
	unsigned f4;
};

int fn_801600F4(Obj801600F4* o, unsigned char k)
{
	switch ((o->f4 >> (k * 4 + 14)) & 7) {
		case 3:
		case 0:
			return 2;
		case 4:
		case 1:
			return 3;
		case 5:
		case 2:
			return 4;
		default:
			return 0;
	}
}
}
