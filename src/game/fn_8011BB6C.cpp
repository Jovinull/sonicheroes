// Copies five floats between records (+8..+0x18).
struct Rec8011BB6C {
	unsigned char pad0[8];
	float f8;
	float fC;
	float f10;
	float f14;
	float f18;
};

extern "C" {
void fn_8011BB6C(Rec8011BB6C* d, Rec8011BB6C* s)
{
	d->f14 = s->f14;
	d->f18 = s->f18;
	d->fC  = s->fC;
	d->f10 = s->f10;
	d->f8  = s->f8;
}
}
