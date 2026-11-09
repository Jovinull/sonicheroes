// Returns the word at offset 0x28.

extern "C" {
struct Obj8011EFB0 {
	unsigned char pad[0x28];
	int v;
};
int fn_8011EFB0(Obj8011EFB0* s)
{
	return s->v;
}
}
