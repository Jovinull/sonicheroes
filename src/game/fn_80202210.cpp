// Clears the state word and releases the two owned blocks (+4 and +0xC); returns arg0.

extern "C" {
struct Obj80202210 {
	int f0;
	unsigned f4;
	int f8;
	int fc;
};
void fn_80194628(unsigned);

Obj80202210* fn_80202210(Obj80202210* o)
{
	o->f0 = 0;
	if (o->f4 != 0) {
		fn_80194628(o->f4);
	}
	o->f4 = 0;
	if ((unsigned)o->fc != 0) {
		fn_80194628(o->fc);
	}
	o->fc = 0;
	return o;
}
}
