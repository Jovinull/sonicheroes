// Reports whether the word at +0x628 of the object is in 8..13.
struct Obj80089134 {
	unsigned char pad0[0x628];
	int f628; // 0x628
};

extern "C" {
int fn_80089134(Obj80089134* o)
{
	switch (o->f628) {
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
			return 1;
	}
	return 0;
}
}
