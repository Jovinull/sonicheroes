// Returns 0 for the listed states and 1 otherwise.
struct Obj80044EC4 {
	unsigned char pad0[0x6F0];
	short f6F0;
};

extern "C" {
int fn_80044EC4(Obj80044EC4* o)
{
	switch (o->f6F0) {
		case 0x27:
		case 0x2A:
		case 0x2B:
		case 0x2C:
		case 0x2D:
		case 0x33:
		case 0x55:
			return 0;
	}
	return 1;
}
}
