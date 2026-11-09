// Increments word 0x40 when it is in 0..4.

extern "C" {
struct Obj80137474 {
	unsigned char pad[0x40];
	int f40;
};

void fn_80137474(Obj80137474* o)
{
	int t = o->f40;
	if (t >= 0 && t < 5) {
		o->f40 = t + 1;
	}
}
}
