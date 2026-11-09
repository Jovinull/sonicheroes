// Returns an angle class 1-4 for the difference between the angle from fn_800E27D8 and the object's heading at 0x10 (thresholds 0x6000, 0x3400, 0x1400); 0 when flag 0x4000 is set or there is no angle.

extern "C" {
struct Obj800E2120 {
	unsigned char pad[6];
	short s6;
	unsigned char pad1[0x10 - 8];
	int f10;
};
int DiffAngle__Fii(int, int);
int fn_800E27D8(Obj800E2120*, int, int*, int);

int fn_800E2120(Obj800E2120* o, int x)
{
	int sp;
	int t;
	if ((o->s6 & 0x4000) != 0) {
		return 0;
	}
	if (fn_800E27D8(o, x, &sp, 0) == 0) {
		return 0;
	}
	t = DiffAngle__Fii(sp, o->f10);
	if (t > 0x6000) {
		return 1;
	}
	if (t > 0x3400) {
		return 2;
	}
	if (t > 0x1400) {
		return 3;
	}
	return 4;
}
}
