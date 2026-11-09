// Trivial accessor.

extern "C" {
struct S3 {
	unsigned char pad[4];
	int f4;
};

int fn_8011BB2C(S3* o)
{
	return o->f4 * 0x1c;
}
}
