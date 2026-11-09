// Allocates an effect record with fn_800B55E4(a, b, 0, 0), sets its type 5, the byte pair at 7/8 to c and word 0x1C to d; returns 1, or 0 when there is none.

extern "C" {
struct Eff800B52E8 {
	unsigned char pad[7];
	signed char b7;
	signed char b8;
	unsigned char pad1[3];
	int fc;
	unsigned char pad2[0x1c - 0x10];
	int f1c;
};
Eff800B52E8* fn_800B55E4(int, int, int, int);

int fn_800B52E8(int a, int b, signed char c, int d)
{
	Eff800B52E8* t = fn_800B55E4(a, b, 0, 0);
	if (t == 0) {
		return 0;
	}
	t->fc  = 5;
	t->b8  = c;
	t->b7  = c;
	t->f1c = d;
	return 1;
}
}
