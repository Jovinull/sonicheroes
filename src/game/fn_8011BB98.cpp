// Builds the 2D rotation entries (cos, -sin, sin, cos) from the angle at +8 and copies the translation at +0xC/+0x10.
struct M8011BB98 {
	float f0;
	float f4;
	unsigned char pad8[8];
	float f10;
	float f14;
	unsigned char pad18[0x18];
	float f30;
	float f34;
};
struct S8011BB98 {
	unsigned char pad0[8];
	float f8;
	float fC;
	float f10;
};

extern "C" {
double cos(double x);
double sin(double x);

void fn_8011BB98(M8011BB98* m, S8011BB98* s)
{
	m->f0  = (float)cos(s->f8);
	m->f4  = (float)-sin(s->f8);
	m->f10 = (float)sin(s->f8);
	m->f14 = (float)cos(s->f8);
	m->f30 = s->fC;
	m->f34 = s->f10;
}
}
