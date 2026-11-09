// Copies three words from the source to the destination.

extern "C" {
struct Vec800EA930 {
	int a;
	int b;
	int c;
};

void fn_800EA930(Vec800EA930* o, Vec800EA930* s)
{
	o->a = s->a;
	o->b = s->b;
	o->c = s->c;
}
}
