// Maps the mode at +0xC to a count (1 -> arg0[8] - 2, 2 -> arg0[8] - 3); any other mode logs 0x102 through fn_8019408C/fn_80193FE8 and returns 0.

extern "C" {
struct Obj8014D194 {
	unsigned char pad[8];
	int f8;
	int fc;
};
int fn_8019408C(int, ...);
void fn_80193FE8(int*);

int fn_8014D194(Obj8014D194* o)
{
	int sp[2];
	switch (o->fc) {
		case 1:
			return o->f8 - 2;
		case 2:
			return o->f8 - 3;
		default:
			sp[0] = 0x102;
			sp[1] = fn_8019408C(1);
			fn_80193FE8(sp);
			return 0;
	}
}
}
