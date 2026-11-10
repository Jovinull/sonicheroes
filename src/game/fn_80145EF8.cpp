// Stores three values into the object's parameter block and returns the object.
struct T3 {
	int a;
	int b;
	int c;
};
struct O34 {
	unsigned char pad[0x34];
	T3* f34;
};
extern "C" {
O34* fn_80145EF8(O34* o, int a, int b, int c)
{
	T3* t = o->f34;
	t->a  = a;
	t->b  = b;
	t->c  = c;
	return o;
}
}
