// Stores arg1 at +8, arg2 at +0 and arg3 at +4.

extern "C" {
struct Rec8017CA10 {
	int f0;
	int f4;
	int f8;
};

void fn_8017CA10(Rec8017CA10* o, int a, int b, int c)
{
	o->f8 = a;
	o->f0 = b;
	o->f4 = c;
}
}
