// Polls the memory card until the probe settles, stores the mapped state and starts the matching follow-up.
struct O801275E8 {
	unsigned char pad0[4];
	int f4;
	int f8;
};

extern "C" {
int CARDProbeEx(int a, int* b, int* c);
void fn_80127904(O801275E8* o, int a);

void fn_801275E8(O801275E8* o)
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
	if (r == 0) {
		fn_80127904(o, 1);
	} else if (r == -1) {
		fn_80127904(o, 2);
	}
}
}
