// Returns the word at 0x708, or -1 when it is below -2 or at least 99.

extern "C" {
struct Obj80116B68 {
	unsigned char pad[0x708];
	int f708;
};

int fn_80116B68(Obj80116B68* o)
{
	int t = o->f708;
	if (t < -2 || t >= 0x63) {
		return -1;
	}
	return t;
}
}
