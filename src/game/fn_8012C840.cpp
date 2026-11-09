// Clears the four words of the record.

extern "C" {
struct Rec8012C840 {
	int a;
	int b;
	int c;
	int d;
};

void fn_8012C840(Rec8012C840* o)
{
	o->a = 0;
	o->b = 0;
	o->c = 0;
	o->d = 0;
}
}
