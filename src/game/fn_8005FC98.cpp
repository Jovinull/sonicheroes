// Packs the two float triples into local vectors and forwards them to fn_8005FBBC.
struct V8005FC98 {
	float x;
	float y;
	float z;
};

extern "C" {
void fn_8005FBBC(V8005FC98* a, V8005FC98* b, int c);

void fn_8005FC98(int c, float ax, float ay, float az, float bx, float by, float bz)
{
	V8005FC98 a;
	V8005FC98 b;
	a.x = ax;
	a.y = ay;
	a.z = az;
	b.x = bx;
	b.y = by;
	b.z = bz;
	fn_8005FBBC(&a, &b, c);
}
}
