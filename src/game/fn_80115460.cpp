// Increments word 0x2C when it is not negative.

extern "C" {
struct Obj80115460 {
	unsigned char pad[0x2c];
	int f2c;
};

void fn_80115460(Obj80115460* o)
{
	int t = o->f2c;
	if (t >= 0) {
		o->f2c = t + 1;
	}
}
}
