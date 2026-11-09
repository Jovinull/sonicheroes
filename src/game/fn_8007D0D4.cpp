// Maps the counter at 0xA4E (4 and up) to a level 1-4 (thresholds 6, 10, 20) and passes it to fn_800908C0 with the linked record at 0x9B8.

extern "C" {
struct Obj8007D0D4 {
	unsigned char pad[0x9b8];
	int f9b8;
	unsigned char pad1[0xa4e - 0x9bc];
	short fa4e;
};
void fn_800908C0(int, int, int);

void fn_8007D0D4(Obj8007D0D4* o)
{
	short t = o->fa4e;
	int v;
	if (t >= 4) {
		if (t >= 0x14) {
			v = 4;
		} else if (t >= 0xa) {
			v = 3;
		} else if (t >= 6) {
			v = 2;
		} else {
			v = 1;
		}
		fn_800908C0(o->f9b8, 0, v);
	}
}
}
