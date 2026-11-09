// Clears the three words at +0, +4, +8.

extern "C" {
struct Rec80154EEC {
	int f0;
	int f4;
	int f8;
};

void fn_80154EEC(Rec80154EEC* o)
{
	o->f8 = 0;
	o->f0 = 0;
	o->f4 = 0;
}
}
