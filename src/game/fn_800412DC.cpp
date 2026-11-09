// Revalidates the cached block at 0x678 (value check via fn_80041378, remembering sp8 in 0x67C) and re-fetches it into 0x680 when it is gone; returns 1.

extern "C" {
struct Obj800412DC {
	unsigned char pad[0x678];
	unsigned f678;
	int f67c;
	unsigned f680;
	unsigned char f684[1];
	unsigned char pad1[0x700 - 0x685];
	int f700;
};
unsigned fn_80041378(void*, int, int, void*);

int fn_800412DC(Obj800412DC* o)
{
	int sp8;
	if (o->f678 != 0) {
		sp8 = 0;
		if (o->f678 == fn_80041378(o, 0x4000 - o->f700, 0x3000, &sp8)) {
			o->f67c = sp8;
		} else {
			o->f678 = 0;
		}
	}
	if (o->f678 == 0) {
		o->f680 = fn_80041378(o, 0x4000 - o->f700, 0x3000, o->f684);
	}
	return 1;
}
}
