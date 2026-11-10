// Copies the three-float vector into both slots of the destination.
struct V3 {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
};

extern "C" {
void fn_80199F50(V3* o, V3* s)
{
	int t2;
	int t1;
	int t0;
	t0   = s->a;
	t1   = s->b;
	o->d = t0;
	t2   = s->c;
	o->e = t1;
	o->f = t2;
	o->a = t0;
	o->b = t1;
	o->c = t2;
}
}
