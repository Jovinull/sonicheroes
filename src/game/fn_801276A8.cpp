// Polls the memory card until the probe settles and applies the new state, returning 1 when the follow-up started.
struct O801276A8 {
	unsigned char pad0[4];
	int f4;
	int f8;
	unsigned char padC[0x10];
	int f1C;
};

extern "C" {
int CARDProbeEx(int a, int* b, int* c);
void fn_80127808(O801276A8* o);

int fn_801276A8(O801276A8* o)
{
	int spC;
	int sp8;
	int r;
	int v;
	do {
		r = CARDProbeEx(o->f4, &sp8, &spC);
	} while (r == -1);
	switch (r) {
		default:
		case -128:
			v = 2;
			break;
		case -3:
		case -1:
			v = 3;
			break;
		case -2:
			v = 4;
			break;
		case 0:
			v = 0;
			break;
	}
	o->f8 = v;
	if (r != 0) {
		o->f1C = o->f8;
		fn_80127808(o);
		return 1;
	}
	return 0;
}
}
