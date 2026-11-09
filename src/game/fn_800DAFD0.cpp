// Unless flag 0x4000 of the halfword at 6 is set, picks the value for word 0x1C of b (from fn_800E27D8 or the word at 0x10 of a) and runs fn_800E1508.

extern "C" {
struct Obj800DAFD0 {
	unsigned char pad[6];
	short s6;
	unsigned char pad1[0x10 - 8];
	int f10;
};
struct Out800DAFD0 {
	unsigned char pad[0x1c];
	int f1c;
};
int fn_800E27D8(Obj800DAFD0*, int, int*, int);
void fn_800E1508(Obj800DAFD0*, Out800DAFD0*, int, int);

void fn_800DAFD0(Obj800DAFD0* a, Out800DAFD0* b, int c)
{
	int sp;
	if ((a->s6 & 0x4000) == 0) {
		if (fn_800E27D8(a, c, &sp, 0) == 0) {
			b->f1c = a->f10;
		} else {
			b->f1c = sp;
		}
		fn_800E1508(a, b, c, b->f1c);
	}
}
}
