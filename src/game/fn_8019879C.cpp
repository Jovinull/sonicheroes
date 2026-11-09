// Skips chunks of the stream arg1: reads the remaining length (fn_80192F38) and repeatedly reads a chunk size and skips it until the length reaches 0; returns arg0, or 0 on any failure.

extern "C" {
int fn_80192D88(int, int, int*, int, int);
int fn_80192F38(int, int, unsigned*, int);
unsigned fn_80197D70(int, int);

int fn_8019879C(int a, int h)
{
	unsigned spc;
	int sp8;
	if (fn_80192F38(h, 3, &spc, 0) == 0) {
		return 0;
	}
	while (spc != 0) {
		if (fn_80192D88(h, 0, &sp8, 0, 0) == 0) {
			return 0;
		}
		if (fn_80197D70(h, sp8) == 0) {
			return 0;
		}
		spc -= sp8 + 0xc;
	}
	return a;
}
}
