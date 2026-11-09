// Returns the record flags (+8) masked with arg2, or 0 when the handle or record is null.

extern "C" {
struct Rec8017CA20 {
	unsigned char pad[8];
	unsigned f8;
};

unsigned fn_8017CA20(unsigned a, Rec8017CA20* o, unsigned m)
{
	if (a != 0 && o != 0) {
		return o->f8 & m;
	}
	return 0;
}
}
