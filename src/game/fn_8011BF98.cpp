// Linearly interpolates five float fields of the destination between the two sources with weight t.
struct V8011BF98 {
	unsigned char pad0[8];
	float f8;
	float fC;
	float f10;
	float f14;
	float f18;
};

extern "C" {
extern float lbl_8042EB30;

void fn_8011BF98(V8011BF98* d, V8011BF98* a, V8011BF98* b, float t)
{
	float u = lbl_8042EB30 - t;
	d->f14  = t * b->f14 + u * a->f14;
	d->f18  = t * b->f18 + u * a->f18;
	d->fC   = t * b->fC + u * a->fC;
	d->f10  = t * b->f10 + u * a->f10;
	d->f8   = t * b->f8 + u * a->f8;
}
}
