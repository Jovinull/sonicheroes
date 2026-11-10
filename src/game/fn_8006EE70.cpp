// Copies a 3-float vector.
struct V8006EE70 {
	float x;
	float y;
	float z;
};

extern "C" {
void fn_8006EE70(V8006EE70* d, V8006EE70* s)
{
	d->x = s->x;
	d->y = s->y;
	d->z = s->z;
}
}
