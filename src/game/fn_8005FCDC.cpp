// Packs the two float triples into local vectors and forwards them to fn_8005FBBC with index -1.
struct V8005FCDC {
	float x;
	float y;
	float z;
};

extern "C" {
void fn_8005FBBC(V8005FCDC* a, V8005FCDC* b, int c);

void fn_8005FCDC(float ax, float ay, float az, float bx, float by, float bz)
{
	V8005FCDC a;
	V8005FCDC b;
	a.x = ax;
	a.y = ay;
	a.z = az;
	b.x = bx;
	b.y = by;
	b.z = bz;
	fn_8005FBBC(&a, &b, -1);
}
}
