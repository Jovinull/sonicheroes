// Stores three shorts into the record arg1 (+0, +2, +4).

extern "C" {
struct Rec8015270C {
	short a;
	short b;
	short c;
};

void fn_8015270C(int unused, Rec8015270C* o, short a, short b, short c)
{
	o->a = a;
	o->b = b;
	o->c = c;
}
}
