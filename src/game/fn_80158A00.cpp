// When the key at +0 of arg1 equals arg0, sets the found flag at +4 and returns 0; otherwise returns arg0.

extern "C" {
struct Rec80158A00 {
	unsigned f0;
	int f4;
};

unsigned fn_80158A00(unsigned a, Rec80158A00* o)
{
	if (o->f0 == a) {
		o->f4 = 1;
		return 0;
	}
	return a;
}
}
