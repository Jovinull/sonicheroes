// Maps the 3-bit field at bits 10..12 of +4 to a count (1 -> 3, 3 -> 6, 4 -> 12), 0 otherwise.

extern "C" {
struct Obj801600A8 {
	unsigned char pad[4];
	unsigned f4;
};

int fn_801600A8(Obj801600A8* o)
{
	switch ((o->f4 >> 10) & 7) {
		case 1:
			return 3;
		case 3:
			return 6;
		case 4:
			return 0xc;
		default:
			return 0;
	}
}
}
